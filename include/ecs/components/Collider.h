#pragma once
#include <SFML/System/Vector2.hpp>
#include "../Types.h"

struct AABB {
	sf::Vector2f center;
	sf::Vector2f extents;

	inline bool Intersects(const AABB& bounds) {
		return center.x - extents.x < bounds.center.x + bounds.extents.x &&
			center.x + extents.x > bounds.center.x - bounds.extents.x &&
			center.y - extents.y < bounds.center.y + bounds.extents.y &&
			center.y + extents.y > bounds.center.y - bounds.extents.y;
	}

	AABB()
		: center(), extents(sf::Vector2f(8.0f, 8.0f))
	{
	}
};

COMPONENT Collider {
	sf::Vector2f offset;
	float bounciness;
	AABB bounds;
};
