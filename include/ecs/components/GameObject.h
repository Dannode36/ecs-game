#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../Types.h"

COMPONENT GameObject : public sf::Sprite {
	bool active{ true };
};
