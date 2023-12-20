#pragma once
#include "System.h"
#include "Components.h"

class PhysicsSystem : public System {
public:
	const double GRAVITY = 6.6742E-11;
	const float SIMSPEED = 1.f;
	void Init();
	void Update(double dt);
	Transform* GetOverlapingTransform(Vector2 clickPos);
};
