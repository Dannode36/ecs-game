#include "ui/Button.h"
#include "Input.h"
#include <fmt/format.h>
#include <types.h>

Button::Button() : normal(), hovered(), clicked(), state(Button_Normal), currentSprite(this->normal)
{ }

Button::Button(TexturePtr normal, TexturePtr hovered, TexturePtr clicked, sf::Vector2f position)
    : normal(), hovered(), clicked(), state(Button_Normal), currentSprite(this->normal)
{
    create(normal, hovered, clicked, position);
}

void Button::create(TexturePtr normal, TexturePtr hovered, TexturePtr clicked, sf::Vector2f position) {
    this->normal.setTexture(*normal);
    this->normal.setPosition(position);

    this->hovered.setTexture(*hovered);
    this->hovered.setPosition(position);

    this->clicked.setTexture(*clicked);
    this->clicked.setPosition(position);

    currentSprite = this->normal;
}

void Button::update(sf::Vector2f mousePos) {
    if (currentSprite.getGlobalBounds().contains(mousePos)) {
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
            currentSprite = normal;
        }
        else if (newState == Button_Hovered) {
            currentSprite = hovered;
        }
        else if (newState == Buton_Pressed) {
            currentSprite = clicked;
            event.fire(*this);
        }
        else {
            throw std::exception("fuck... button state is what?");
        }
        state = newState;
    }
}
ButtonState Button::getState() const {
    return state;
}
sf::Sprite* Button::getCurrentSprite() {
    return &currentSprite;
}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(currentSprite);
}
