#pragma once
#include "System.h"
#include "../../InputManager.h"
#include "../Components.h"
class MovementSystem : public System
{
public:
	void Update(InputManager& inputMgr, const sf::Time& dt);
};

