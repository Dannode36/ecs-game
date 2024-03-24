#pragma once
#include <ecs/Types.h>
#include <SFML/System/Vector2.hpp>

COMPONENT Projectile
{
	float speed;
	sf::Vector2f direction;
	int damage;
};
