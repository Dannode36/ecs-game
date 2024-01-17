#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "util/Event.h"

class IGuiElement : public sf::Drawable
{
public:
	Event<bool> clickEvent;
	Event<bool> hoverEvent;
	virtual void handleEvent(sf::Event& event) = 0;
};
