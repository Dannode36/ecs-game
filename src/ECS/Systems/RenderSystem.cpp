#include <iostream>
#include "RenderSystem.h"
#include "../ECS.h"

extern ECS ecs;

void RenderSystem::DrawEntities(sf::RenderWindow& window) {
	for (auto const& entity : mEntities) {

		auto& renderer = ecs.GetComponent<Renderer>(entity);

		if (renderer.active) {
			auto& transform = ecs.GetComponent<Transform>(entity);

			if (transform.parent != NULL) {
				renderer.sprite.setOrigin(transform.parent->position);
			}
			else {
				renderer.sprite.setOrigin(0, 0);
			}

			renderer.sprite.setPosition(transform.position);
			renderer.sprite.setRotation(transform.rotation);
			renderer.sprite.setScale(transform.scale);
			window.draw(renderer.sprite);
		}
	}
}
