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
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (!render) { return; }

        //Sort vector with smallest y first
        std::vector<GameObject*> sortedObjects(m_objects);

        std::sort(sortedObjects.begin(), sortedObjects.end(),
            [](GameObject* a, GameObject* b) -> bool {
                return a->getPosition().y < b->getPosition().y;
            }
        );

        //Draw
        for (auto& object : m_objects) {
            target.draw(*object);
        }
    }

    void sortObjects() {
        std::sort(m_objects.begin(), m_objects.end(),
            [](GameObject* a, GameObject* b) -> bool {
                return a->getPosition().y < b->getPosition().y;
            }
        );
    }

    bool render;
    std::vector<GameObject*> m_objects;
};
