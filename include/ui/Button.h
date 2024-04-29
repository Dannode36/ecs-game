#pragma once
#include "SFML/Graphics.hpp"
#include "util/Event.h"
#include "ui/Widget.h"
#include "types.h"

enum WidgetButtonState {
    Button_None = 0,
    Button_Normal,
    Button_Hovered,
    Buton_Pressed
};

class Button : public Widget {
private:
    TexturePtr normal;
    TexturePtr hovered;
    TexturePtr clicked;
    sf::Sprite sprite;
    WidgetButtonState state;

public:
    Event<Button> event;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Button() = default;
    Button(TexturePtr normal, TexturePtr hovered, TexturePtr clicked, sf::Vector2f position);

    void update(sf::Vector2f mousePos = sf::Vector2f(0, 0));
    void setState(WidgetButtonState clicked);
    WidgetButtonState getState() const;
    sf::Sprite* getCurrentSprite();

    // Inherited via Widget
    void handleEvent(sf::Event& event) override;
};
