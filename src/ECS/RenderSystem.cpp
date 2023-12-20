#include "RenderSystem.h"
#include "ECS.h"
#include <iostream>

extern ECS gECS;

void RenderSystem::Draw(sf::RenderWindow& window) {
	window.clear(sf::Color::Black);
	sf::VertexArray vertArray;

	for (auto const& entity : mEntities){
		auto& transform = gECS.GetComponent<Transform>(entity);
		auto& renderer = gECS.GetComponent<Renderer>(entity);
		float radius = transform.radius;

		sf::CircleShape circle(radius, 32);
		circle.setFillColor(renderer.color);
		circle.setPosition(transform.pos.x - radius, transform.pos.y - radius);
		window.draw(circle);
	}
}
