#include <iostream>
#include "RenderSystem.h"
#include "ECS.h"

extern ECS ecs;

void RenderSystem::DrawEntities(sf::RenderWindow& window) {
	for (auto const& entity : mEntities){
		auto& transform = ecs.GetComponent<Transform>(entity);
		auto& renderer = ecs.GetComponent<Renderer>(entity);
		float radius = transform.radius;

		sf::CircleShape circle(radius, 32);
		circle.setFillColor(renderer.color);
		circle.setPosition(transform.pos.x - radius, transform.pos.y - radius);
		window.draw(circle);
	}
}
