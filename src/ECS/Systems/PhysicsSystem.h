#pragma once
#include "System.h"
#include "../Components.h"

class PhysicsSystem : public System {
public:
	const float SIMSPEED = 1.0f;
	void Init();
	void Update(double dt);
};
