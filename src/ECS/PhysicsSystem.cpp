#include "PhysicsSystem.h"
#include "ECS.h"
#include "CONSTANTS.h"
#include "Components.h"
#include <iostream>
#include <vector>
extern ECS gECS;

void PhysicsSystem::Init() {

}

bool CircleCircleOverlap(Transform& c1, Transform& c2) {
	return pow((c2.pos.x - c1.pos.x), 2) + pow((c2.pos.y - c1.pos.y), 2) <= pow((c1.radius + c2.radius), 2);
}

bool CirclePointOverlap(Transform& circle, Vector2& point) {
	return pow((point.x - circle.pos.x), 2) + pow((point.y - circle.pos.y), 2) <= circle.radius * circle.radius;
}

void checkForAndSolveCollision(Transform& c1, Transform& c2) {
	float dist = static_cast<float>(pow((c2.pos.x - c1.pos.x), 2) + pow((c2.pos.y - c1.pos.y), 2));
	if (dist <= pow((c1.radius + c2.radius), 2)) {
		std::cout << "Collision Found" << "\n";

		dist = sqrt(dist);
		float midpointx{ (c1.pos.x + c2.pos.x) / 2 };
		float midpointy{ (c1.pos.y + c2.pos.y) / 2 };

		//Static Resolution
		c1.pos.x = midpointx + c1.radius * (c1.pos.x - c2.pos.x) / dist;
		c1.pos.y = midpointy + c1.radius * (c1.pos.y - c2.pos.y) / dist;

		c2.pos.x = midpointx + c2.radius * (c2.pos.x - c1.pos.x) / dist;
		c2.pos.y = midpointy + c2.radius * (c2.pos.y - c1.pos.y) / dist;

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
		auto& rigidBody = gECS.GetComponent<RigidBody>(entity);
		auto& transform = gECS.GetComponent<Transform>(entity);

		if (!rigidBody.kinematic) {
			for (auto const& entity : mEntities)
			{
				for (auto const& entity2 : mEntities) {
					if (entity != entity2) {
						auto& transform = gECS.GetComponent<Transform>(entity);
						auto& transform2 = gECS.GetComponent<Transform>(entity2);
						checkForAndSolveCollision(transform, transform2);
					}
				}
			}
		}
	}
}

Transform* PhysicsSystem::GetOverlapingTransform(Vector2 pos) {
	for (auto const& entity : mEntities)
	{
		auto& transform = gECS.GetComponent<Transform>(entity);
		if (CirclePointOverlap(transform, pos)) {
			return &transform;
		}
	}
	return nullptr;
}
