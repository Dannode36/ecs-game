#include "Button.h"
#include "../Input.h"
#include <fmt/format.h>

Button::Button(sf::Texture& normal, sf::Texture& hovered, sf::Texture& clicked, sf::Vector2f position) {
    this->normal.setTexture(normal);
    this->normal.setPosition(position);

    this->hovered.setTexture(hovered);
    this->hovered.setPosition(position);

    this->clicked.setTexture(clicked);
    this->clicked.setPosition(position);

    setState(Button_Normal);
}
void Button::update(sf::Vector2f mousePos) {
    if (currentSprite->getGlobalBounds().contains(mousePos)) {
        bool mouseLeftDown = Input::GetMouseButtonDown(MouseButton::Left);
        bool mouseLeftPressed = Input::GetMouseButton(MouseButton::Left);
        if (mouseLeftDown || (mouseLeftPressed && state == Buton_Pressed)) {
            setState(Buton_Pressed);
        }
        else {
            setState(Button_Hovered);
        }
    }
    else {
        setState(Button_Normal);
    }
}
void Button::setState(ButtonState newState) {
    if (state != newState) {
        state = newState;

        if (state == Button_Normal) {
            currentSprite = &normal;
        }
        else if (state == Button_Hovered) {
            currentSprite = &hovered;
        }
        else if (state == Buton_Pressed) {
            currentSprite = &clicked;
        }
    }
}
ButtonState Button::getState() const {
    return state;
}
sf::Sprite* Button::getCurrentSprite() {
    return currentSprite;
}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*currentSprite);
}
