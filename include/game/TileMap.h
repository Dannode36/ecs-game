#pragma once
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TileLayer.h"
#include <set>
#include "ecs/Components.h"
#include "ObjectLayer.h"
#include <vendor/tileson.hpp>
#include "fmt/format.h"

class Map : public sf::Drawable
{
public:
    enum Layer
    {
        Back = 0,       //Reserved for permanent features
        Buildings,      //Tiles will act like a wall unless "Passable"
        Dynamic,        //Tiles editable by the player
        Front,          //Objects drawn on top if the player is north of them and behind if the player is south of them
        AlwaysFront,    //Objects always drawn top

        Count //Keep Last
    };

    const std::string layerNames[Layer::Count]
    {
        "Back", "Building", "Dynamic", "Front", "Always Front"
    };

    bool load(const std::string& path) {
        tson::Tileson t;
        //std::unique_ptr<tson::Map> map = t.parse(fs::path(path));
        std::unique_ptr<tson::Map> map = t.parse(fs::path("./path/to/map.json"));

        if (map->getStatus() == tson::ParseStatus::OK)
        {
            //Load layers
            for (int i = 0; i < Layer::Count; i++) {
                m_objectLayers[i].load(map->getLayer(layerNames[i] + " Objects"));
                m_tileLayers[i].load(map->getLayer(layerNames[i] + " Tiles"));
            }
            //Gets the layer called "Object Layer" from the "ultimate_demo.json map
            tson::Layer* objectLayer = map->getLayer("Object Layer"); //This is an Object Layer

            //Example from an Object Layer.
            if (objectLayer->getType() == tson::LayerType::ObjectGroup)
            {
                tson::Object* goomba = objectLayer->firstObj("goomba"); //Gets the first object with this name. This can be any object.

                //If you want to just go through every existing object in the layer:
                for (auto& obj : objectLayer->getObjects())
                {
                    tson::Vector2i position = obj.getPosition();
                    tson::Vector2i size = obj.getSize();
                    tson::ObjectType objType = obj.getObjectType();

                    //You may want to check the object type to make sure you use the data right.
                }

                tson::ObjectType objType = goomba->getObjectType();

                if (objType == tson::ObjectType::Rectangle)
                {
                    tson::Vector2i size = goomba->getSize();
                    tson::Vector2i position = goomba->getPosition();

                    //If you have set a custom property, you can also get this
                    int hp = goomba->get<int>("hp");

                    //Using size and position you can can create a Rectangle object by your library of choice.
                    //An example if you were about to use SFML for drawing:
                    //sf::RectangleShape rect;
                    //rect.setSize(sf::Vector2f(size.x, size.y));
                    //rect.setPosition(sf::Vector2f(position.x, position.y));
                }
                else if (objType == tson::ObjectType::Polygon)
                {
                    for (auto const& poly : goomba->getPolygons())
                    {
                        //Set a point on a shape taking polygons
                    }
                    tson::Vector2i position = goomba->getPosition();
                }
                else if (objType == tson::ObjectType::Polyline)
                {
                    std::vector<tson::Vector2i> polys = goomba->getPolylines();
                    for (auto const& poly : goomba->getPolylines())
                    {

                    }
                    tson::Vector2i position = goomba->getPosition();
                }
            }

            tson::Layer* tileLayer = map->getLayer("Main Layer"); //This is a Tile Layer.

            //You can get your tileset like this, but in v1.2.0
            //The tiles themselves holds a pointer to their related tileset.
            tson::Tileset* tileset = map->getTileset("demo-tileset");

            //Example from a Tile Layer
            //I know for a fact that this is a Tile Layer, but you can check it this way to be sure.
            if (tileLayer->getType() == tson::LayerType::TileLayer)
            {
                //pos = position in tile units
                for (auto& [pos, tileObject] : tileLayer->getTileObjects()) //Loops through absolutely all existing tileObjects
                {
                    tson::Tileset* tileset = tileObject.getTile()->getTileset();
                    tson::Rect drawingRect = tileObject.getDrawingRect();
                    tson::Vector2f position = tileObject.getPosition();

                    //Here you can determine the offset that should be set on a sprite
                    //Example on how it would be done using SFML (where sprite presumably is a member of a generated game object):
                    //sf::Sprite *sprite = storeAndLoadImage(tileset->getImage().u8string(), {0, 0});
                    //if (sprite != nullptr)
                    //{
                    //    sprite->setTextureRect({drawingRect.x, drawingRect.y, drawingRect.width, drawingRect.height});
                    //    sprite->setPosition({position.x, position.y});
                    //    m_window.draw(*sprite);
                    //}
                }
            }
        }
        else {
#if DEBUG_LEVEL >= DEBUG_CRITICAL
            fmt::print("Tilemap failed to load:\n-->Path: {0}\n-->Tileson Status: {1}", path, (int)map->getStatus());
#endif
            return false;
        }
    }

    void sortObjectLayers() {
        for (int i = 0; i < Layer::Count; i++) {
            m_objectLayers[i].sort();
        }
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        //Draw tile layers
        for (auto& layer : m_tileLayers)
        {
            target.draw(layer);
        }

        for (int i = 0; i < Layer::Count; i++) {
            target.draw(m_tileLayers[i]);
            target.draw(m_objectLayers[i]);
        }
    }

    sf::Vector2u tileSizePixels;
    sf::Vector2u mapSizeTiles;

    GameObject player;
    TileLayer m_tileLayers[Layer::Count]; //Higher index -> drawn last
    ObjectLayer m_objectLayers[Layer::Count]; //Higher index -> drawn last
};
