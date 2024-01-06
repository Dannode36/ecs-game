#pragma once
#include "SFML/Graphics.hpp"

enum ButtonState {
    Button_None = 0,
    Button_Normal,
    Button_Hovered,
    Buton_Pressed
};

class Button : public sf::Drawable {
public:
    Button() = default;
    Button(sf::Texture& normal, sf::Texture& hovered, sf::Texture& clicked, sf::Vector2f position);

    void update(sf::Vector2f mousePos);
    void setState(ButtonState clicked);
    ButtonState getState() const;
    sf::Sprite* getCurrentSprite();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite normal;
    sf::Sprite hovered;
    sf::Sprite clicked;
    sf::Sprite* currentSprite;
    ButtonState state;
};
