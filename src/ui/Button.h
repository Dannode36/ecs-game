#pragma once
#include "SFML/Graphics.hpp"
#include "util/Event.h"

enum ButtonState {
    Button_None = 0,
    Button_Normal,
    Button_Hovered,
    Buton_Pressed
};

class Button : public sf::Drawable {
private:
    sf::Sprite normal;
    sf::Sprite hovered;
    sf::Sprite clicked;
    sf::Sprite* currentSprite;
    ButtonState state;

public:
    Event<Button> event;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Button() = default;
    Button(sf::Texture& normal, sf::Texture& hovered, sf::Texture& clicked, sf::Vector2f position);
    Button(std::shared_ptr<sf::Texture> normal, std::shared_ptr<sf::Texture> hovered, std::shared_ptr<sf::Texture> clicked, sf::Vector2f position);

    void update(sf::Vector2f mousePos = sf::Vector2f(0, 0));
    void setState(ButtonState clicked);
    ButtonState getState() const;
    sf::Sprite* getCurrentSprite();
};
