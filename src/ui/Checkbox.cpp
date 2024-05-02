#include "ui/Checkbox.h"
#include "Input.h"
#include <fmt/format.h>
#include <types.h>

Checkbox::Checkbox(TexturePtr normal, TexturePtr hover, TexturePtr checkmark, sf::Vector2f position)
    : checked(false), hovered(false)
{
    this->normal = normal;
    this->hover = hover;
    this->checkmark = checkmark;

    sprite.setTexture(*normal);
    sprite.setPosition(position);
    checkmarkSprite.setTexture(*checkmark);
    checkmarkSprite.setPosition(position);
}
void Checkbox::setState(bool checked, bool hovered) {
    if (hovered) {
        sprite.setTexture(*hover);
    }
    else {
        sprite.setTexture(*normal);
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

void Checkbox::update(sf::Vector2f mousePos) {

    if (sprite.getGlobalBounds().contains(mousePos)) {
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
void Checkbox::handleEvent(sf::Event& event) {
    update();
}

sf::Vector2f Checkbox::getSize() {
    return sprite.getLocalBounds().getSize();
}

sf::Vector2f Checkbox::getPosition() {
    return sprite.getPosition();
}

void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
    if (checked) {
        target.draw(checkmarkSprite);
    }
}
