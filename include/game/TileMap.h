#pragma once
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TileLayer.h"
#include <set>
#include "ecs/Components.h"
#include "ObjectLayer.h"

class TileMap : public sf::Drawable
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

    bool load(const std::string& map) {

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
