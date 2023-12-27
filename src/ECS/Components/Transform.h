#pragma once
#include "../Types.h"
struct Transform {
	Transform* parent{};

	sf::Vector2f position{ 0, 0 };
	float rotation{ 0.0 }; //In degrees
	sf::Vector2f scale{ 0, 0 };
};
