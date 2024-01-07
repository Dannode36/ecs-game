#pragma once
#include "System.h"
#include "../../Input.h"
#include "../Components.h"
class MovementSystem : public System
{
public:
	void Update(const sf::Time& dt);
};

