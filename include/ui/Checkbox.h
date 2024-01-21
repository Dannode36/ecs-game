#pragma once
#include "SFML/Graphics.hpp"
#include "util/Event.h"
#include "types.h"
#include "GuiElement.h"

class Checkbox : public IGuiElement {
private:
    TexturePtr normal;
    TexturePtr hover;
    TexturePtr checkmark;
    sf::Sprite sprite;
    sf::Sprite checkmarkSprite;

public:
    bool checked;
    bool hovered;
    Event<bool> checkEvent;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(sf::Vector2f mousePos = sf::Vector2f(0, 0));

public:
    Checkbox() = default;
    Checkbox(TexturePtr normal, TexturePtr hovered, TexturePtr clicked, sf::Vector2f position);

    void setState(bool checked, bool hovered);

    // Inherited via IGuiElement
    void handleEvent(sf::Event& event) override;
};
