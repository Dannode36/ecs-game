#pragma once

#pragma once
#include "SFML/Graphics.hpp"
#include "util/Event.h"
#include "types.h"

class Checkbox : public sf::Drawable {
private:
    sf::Sprite normal;
    sf::Sprite hover;
    sf::Sprite check;
    sf::Sprite* currentSprite;

    bool checked;
    bool hovered;

public:
    Event<bool> event;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Checkbox() = default;
    Checkbox(sf::Texture& normal, sf::Texture& hovered, sf::Texture& clicked, sf::Vector2f position);
    Checkbox(TexturePtr normal, TexturePtr hovered, TexturePtr clicked, sf::Vector2f position);

    void update(sf::Vector2f mousePos = sf::Vector2f(0, 0));
    void setState(bool checked, bool hovered);
    sf::Sprite* getCurrentSprite();
};
