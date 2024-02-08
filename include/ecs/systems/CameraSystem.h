#pragma once
#include "ecs/systems/System.h"
#include "SFML/Graphics/View.hpp"
#include <SFML/System/Time.hpp>
#include <ecs/components/Camera.h>

class CameraSystem : public System
{
public:
	void Update(sf::Time dt, sf::Vector2f pos);
};
