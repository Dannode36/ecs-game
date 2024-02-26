#pragma once
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TileLayer.h"
#include <set>

class TileMap : public sf::Drawable, public sf::Transformable
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
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);

        for (auto& layer : m_layers)
        {
            layer.sort();
            for (auto& drawable : layer)
            {
                drawable
            }
        }
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    sf::Vector2u tileSizePixels;
    sf::Vector2u mapSizeTiles;
    std::vector<Tile> m_tiles;

    std::vector<ObjectLayer> m_objectLayers[Layer::Count]; //Higher index -> drawn last
    std::vector<TileLayer> m_tileLayers[Layer::Count]; //Higher index -> drawn last
};
