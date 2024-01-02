#include <iostream>
#include "RenderSystem.h"
#include "../ECS.h"

extern ECS ecs;

void RenderSystem::DrawEntities(sf::RenderWindow& window) {
	for (auto const& entity : mEntities) {
		auto& renderer = ecs.GetComponent<GameObject>(entity);
		window.draw(renderer.sprite);
	}
}
