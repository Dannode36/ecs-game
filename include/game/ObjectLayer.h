#pragma once
#pragma once
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.h"

class ObjectLayer : public sf::Drawable, public sf::Transformable
{
public:
    //bool load();
    ObjectLayer& sort() {
        std::sort(m_objects.begin(), m_objects.end(),
            [](GameObject* a, GameObject* b) -> bool {
                return a->getPosition().y < b->getPosition().y;
            }
        );
        return *this;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto& object : m_objects) {
            target.draw(*object);
        }
    }

    bool render;
    std::vector<GameObject*> m_objects;
};
