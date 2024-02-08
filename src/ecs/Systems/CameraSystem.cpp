#include <ecs/ECS.h>
#include "ecs/systems/CameraSystem.h"

extern ECS ecs;

void CameraSystem::Update(sf::Time dt, sf::Vector2f pos) {
	for (auto& camEntity : mEntities) {
		auto& cam = ecs.GetComponent<Camera>(camEntity);

		auto camToPosDir = pos - cam.view->getCenter();
		cam.view->move(camToPosDir * dt.asSeconds() * cam.speed);
	}
}
