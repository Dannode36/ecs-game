#include <iostream>
#include <vector>
#include "PhysicsSystem.h"
#include "../ECS.h"
#include "../CONSTANTS.h"
#include "../Components.h"
#include "../ecsmathf.h"

extern ECS ecs;

void PhysicsSystem::Init() {

}

void checkForAndSolveCollision(Transform& c1, Transform& c2) {
	float dist = static_cast<float>(pow((c2.position.x - c1.position.x), 2) + pow((c2.position.y - c1.position.y), 2));
	if (dist <= pow((c1.radius + c2.radius), 2)) {

		dist = sqrt(dist);
		float midpointx{ (c1.position.x + c2.position.x) / 2 };
		float midpointy{ (c1.position.y + c2.position.y) / 2 };

		//Static Resolution
		c1.position.x = midpointx + c1.radius * (c1.position.x - c2.position.x) / dist;
		c1.position.y = midpointy + c1.radius * (c1.position.y - c2.position.y) / dist;

		c2.position.x = midpointx + c2.radius * (c2.position.x - c1.position.x) / dist;
		c2.position.y = midpointy + c2.radius * (c2.position.y - c1.position.y) / dist;

		//Dynamic Resolution
		/*double d = sqrt(pow(c1.pos.x - c2.pos.x, 2) + pow(c1.pos.y - c2.pos.y, 2));
		double nx = (c2.pos.x - c1.pos.x) / d;
		double ny = (c2.pos.y - c1.pos.y) / d;
		double p = 2 * (circle1.vx * nx + circle1.vy * ny - circle2.vx * nx - circle2.vy * ny) / (c1Mass + c2Mass);

		vx1 = circle1.vx - p * circle1.mass * nx;
		vy1 = circle1.vy - p * circle1.mass * ny;
		vx2 = circle2.vx + p * circle2.mass * nx;
		vy2 = circle2.vy + p * circle2.mass * ny;*/
	}
}

void PhysicsSystem::Update(double dt) {
	for (auto const& entity : mEntities)
	{
		auto& rigidBody = ecs.GetComponent<RigidBody>(entity);
		auto& transform = ecs.GetComponent<Transform>(entity);

		if (!rigidBody.kinematic) {
			for (auto const& entity : mEntities)
			{
				for (auto const& entity2 : mEntities) {
					if (entity != entity2) {
						auto& transform = ecs.GetComponent<Transform>(entity);
						auto& transform2 = ecs.GetComponent<Transform>(entity2);
						checkForAndSolveCollision(transform, transform2);
					}
				}
			}
		}
	}
}

Transform* PhysicsSystem::GetOverlapingTransform(Vector2 position) {
	for (auto const& entity : mEntities)
	{
		auto& transform = ecs.GetComponent<Transform>(entity);
		if (CirclePointOverlap(transform, position)) {
			return &transform;
		}
	}
	return nullptr;
}
