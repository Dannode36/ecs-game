#pragma once
#include "SFML/Graphics/View.hpp"

struct Camera {
	sf::View* view;
	float speed;

	Camera() = default;
	Camera(sf::View& view, float speed)
		: view(&view), speed(speed)
	{
	}
};
