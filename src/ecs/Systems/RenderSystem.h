#pragma once
#include "System.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class RenderSystem : public System {
public:
	void DrawEntities(sf::RenderWindow& window);
	bool debugRender{ false };
};
