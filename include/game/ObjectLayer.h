#pragma once
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vendor/tileson.hpp>

class ObjectLayer : public sf::Drawable, public sf::Transformable
{
public:
    bool load(tson::Layer* tsonLayer) {
        if (tsonLayer == nullptr || tsonLayer->getType() != tson::LayerType::ObjectGroup) {
            return false;
        }

        //create gameobjects
    }
    ObjectLayer& sort() {
        std::sort(m_objects.begin(), m_objects.end(),
            [](GameObject* a, GameObject* b) -> bool {
                return a->getPosition().y < b->getPosition().y;
            }
        );
        return *this;
    }

private:
    //A call must be made to sort() prior to drawing for correct draw order
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (auto& object : m_objects) {
            target.draw(*object);
        }
    }

    bool render;
    std::vector<GameObject*> m_objects;
};
