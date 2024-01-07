#include "ui/Button.h"
#include "Input.h"
#include <fmt/format.h>
#include <types.h>

Button::Button(sf::Texture& normal, sf::Texture& hovered, sf::Texture& clicked, sf::Vector2f position) : normal(), hovered(), clicked(), state(Button_Normal) {
    this->normal.setTexture(normal);
    this->normal.setPosition(position);

    this->hovered.setTexture(normal);
    this->hovered.setPosition(position);

    this->clicked.setTexture(clicked);
    this->clicked.setPosition(position);
    currentSprite = nullptr;
}

Button::Button(TexturePtr normal, TexturePtr hovered, TexturePtr clicked, sf::Vector2f position)
    : normal(), hovered(), clicked(), state(Button_Normal)
{
    this->normal.setTexture(*normal);
    this->normal.setPosition(position);

    this->hovered.setTexture(*normal);
    this->hovered.setPosition(position);

    this->clicked.setTexture(*clicked);
    this->clicked.setPosition(position);
    currentSprite = nullptr;
}

void Button::update(sf::Vector2f mousePos) {
    if (currentSprite == nullptr) {
        currentSprite = &normal;
    }

    if (currentSprite->getGlobalBounds().contains(mousePos)) {
        if (state == Buton_Pressed && Input::GetMouseButton(MouseButton::Left)) {
            return; //Do nuthin
        }
        else if (Input::GetMouseButtonDown(MouseButton::Left)) 
        {
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
        if (newState == Button_Normal) {
            currentSprite = &normal;
        }
        else if (newState == Button_Hovered) {
            currentSprite = &hovered;
        }
        else if (newState == Buton_Pressed) {
            currentSprite = &clicked;
            event.fire(*this);
        }
        state = newState;
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
