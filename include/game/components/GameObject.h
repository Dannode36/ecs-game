#pragma once
#include <SFML/Graphics/Sprite.hpp>

struct Object : public sf::Sprite {
	bool active{ true };
};
