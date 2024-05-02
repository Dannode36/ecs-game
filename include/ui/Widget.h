#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "util/Event.h"

class Widget : public sf::Drawable
{
public:
	Event<bool> clickEvent;
	Event<bool> hoverEvent;

	virtual void handleEvent(sf::Event& mousePos) = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual sf::Vector2f getSize() = 0;
};
