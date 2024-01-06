#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../Types.h"

Component GameObject {
	sf::Sprite sprite;
	bool active{ true };
};
