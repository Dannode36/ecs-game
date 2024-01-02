#include "MovementSystem.h"
#include "../ECS.h"
#include <mathf.h>

extern ECS ecs;

void MovementSystem::Update(InputManager& input, const sf::Time& dt)
{
	for (auto const& entity : mEntities) {
		sf::Vector2f move;
		auto& object = ecs.GetComponent<GameObject>(entity);
		auto& movementData = ecs.GetComponent<MovementController>(entity);

		if (input.GetKey(KeyCode::W)) {
			move.y += -1;
		}
		if (input.GetKey(KeyCode::A)) {
			move.x += -1;
		}
		if (input.GetKey(KeyCode::S)) {
			move.y += 1;
		}
		if (input.GetKey(KeyCode::D)) {
			move.x += 1;
		}

		object.sprite.move(normalize(move) * movementData.speed * dt.asSeconds());
	}
}
