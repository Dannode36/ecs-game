#pragma once
#include <SFML/Window/Event.hpp>
#include "util/Event.h"

class IGuiElement
{
public:
	Event<bool> clickEvent;
	Event<bool> hoverEvent;
	virtual void handleEvent(sf::Event& event) = 0;
};
