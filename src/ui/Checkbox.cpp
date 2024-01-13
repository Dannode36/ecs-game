#include "ui/Checkbox.h"
#include "Input.h"
#include <fmt/format.h>
#include <types.h>

Checkbox::Checkbox(sf::Texture& normal, sf::Texture& hover, sf::Texture& check, sf::Vector2f position)
    : normal(), hover(), check(), checked(), hovered() 
{
    this->normal.setTexture(normal);
    this->normal.setPosition(position);

    this->hover.setTexture(hover);
    this->hover.setPosition(position);

    this->check.setTexture(check);
    this->check.setPosition(position);
    currentSprite = nullptr;
}
Checkbox::Checkbox(TexturePtr normal, TexturePtr hover, TexturePtr check, sf::Vector2f position)
    : normal(), hover(), check(), checked(), hovered()
{
    this->normal.setTexture(*normal);
    this->normal.setPosition(position);

    this->hover.setTexture(*hover);
    this->hover.setPosition(position);

    this->check.setTexture(*check);
    this->check.setPosition(position);
    currentSprite = nullptr;
}

void Checkbox::update(sf::Vector2f mousePos) {
    if (currentSprite == nullptr) {
        currentSprite = &normal;
    }

    if (currentSprite->getGlobalBounds().contains(mousePos)) {
        if (Input::GetMouseButtonDown(MouseButton::Left)) {
            setState(!checked, true);
        }
        else {
            setState(checked, true);
        }
    }
    else {
        setState(checked, false);
    }
}
void Checkbox::setState(bool checked, bool hovered) {
    if (hovered) {
        currentSprite = &hover;
    }
    else {
        currentSprite = &normal;
    }

    if (this->checked != checked) {
        checkEvent.fire(checked);
    }
    if (this->hovered != hovered) {
        hoverEvent.fire(hovered);
    }

    this->checked = checked;
    this->hovered = hovered;
}
sf::Sprite* Checkbox::getCurrentSprite() {
    return currentSprite;
}
void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*currentSprite);
    if (checked) {
        target.draw(check);
    }
}
