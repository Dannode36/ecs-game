#pragma once
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TileLayer.h"
#include <set>
#include "GameObject.h"

class TileMap : public sf::Drawable
{
public:
    enum Layer
    {
        Back = 0,       //Reserved for permanent features TileLayer
        Buildings,      //Tiles will act like a wall unless "Passable"
        Flooring,       //Tiles editable by the player
        Front,          //Objects drawn on top if the player is north of them and behind if the player is south of them
        AlwaysFront,    //Objects always drawn top

        Count //Keep Last
    };

    bool load(const std::string& map) {
        
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        //Draw tile layers
        for (auto& layer : m_tileLayers)
        {
            target.draw(layer);
        }

        std::vector<const GameObject*> objectsInFront;

        //Draw objects behind player
        float playerY = player.getPosition().y;
        for (auto& object : m_objects)
        {
            if (object.getPosition().y < playerY) {
                target.draw(object);
            }
            else {
                objectsInFront.push_back(&object);
            }
        }

        //Draw player
        target.draw(player);

        //Draw objects infront of player
        for (auto& object : objectsInFront)
        {
            target.draw(*object);
        }
    }

    sf::Vector2u tileSizePixels;
    sf::Vector2u mapSizeTiles;

    GameObject player;
    std::vector<GameObject> m_objects;
    TileLayer m_tileLayers[Layer::Count]; //Higher index -> drawn last
};
