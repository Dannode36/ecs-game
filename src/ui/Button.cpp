#include "ui/Button.h"
#include "Input.h"
#include <fmt/format.h>
#include <types.h>

Button::Button(TexturePtr normal, TexturePtr hovered, TexturePtr clicked, sf::Vector2f position)
{
    this->normal = normal;
    this->hovered = hovered;
    this->clicked = clicked;

    sprite.setTexture(*normal);
    sprite.setPosition(position);
    event.clear();
}

void Button::update(sf::Vector2f mousePos) {
    if (sprite.getGlobalBounds().contains(mousePos)) {
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
void Button::setState(WidgetButtonState newState) {
    if (state != newState) {
        if (newState == Button_Normal) {
            sprite.setTexture(*normal);
        }
        else if (newState == Button_Hovered) {
            sprite.setTexture(*hovered);
        }
        else if (newState == Buton_Pressed) {
            sprite.setTexture(*clicked);
            event.fire(*this);
        }
        else {
            throw std::exception("fuck... button state is none???");
        }
        state = newState;
    }
}
WidgetButtonState Button::getState() const {
    return state;
}
sf::Sprite* Button::getCurrentSprite() {
    return &sprite;
}
void Button::handleEvent(sf::Event& event) {
    //switch (event.type)
    //{
    //case sf::Event::MouseMoved:
    //    break;
    //case sf::Event::MouseButtonPressed:
    //    break;
    //default:
    //    break;
    //}
    //if (sprite.getGlobalBounds().contains(mousePos)) {
    //    if (state == Buton_Pressed && Input::GetMouseButton(MouseButton::Left)) {
    //        return; //Do nuthin
    //    }
    //    else if (Input::GetMouseButtonDown(MouseButton::Left))
    //    {
    //        setState(Buton_Pressed);
    //    }
    //    else {
    //        setState(Button_Hovered);
    //    }
    //}
    //else {
    //    setState(Button_Normal);
    //}
}
sf::Vector2f Button::getPosition() {
    return sf::Vector2f();
}
sf::Vector2f Button::getSize() {
    return sf::Vector2f();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}
