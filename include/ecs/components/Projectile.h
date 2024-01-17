#pragma once
#include <ecs/Types.h>
#include <SFML/System/Vector2.hpp>

Component Projectile
{
	float speed;
	sf::Vector2f direction;
	int damage;
};
