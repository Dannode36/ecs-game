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

		if (input.GetKeyDown(KeyCode::W)) {
			printf("W pressed\n");
		}
		if (input.GetKeyDown(KeyCode::A)) {
			printf("A pressed\n");
		}
		if (input.GetKeyDown(KeyCode::S)) {
			printf("S pressed\n");
		}
		if (input.GetKeyDown(KeyCode::D)) {
			printf("D pressed\n");
		}

		if (input.GetKeyUp(KeyCode::W)) {
			printf("W Released\n");
		}
		if (input.GetKeyUp(KeyCode::A)) {
			printf("A Released\n");
		}
		if (input.GetKeyUp(KeyCode::S)) {
			printf("S Released\n");
		}
		if (input.GetKeyUp(KeyCode::D)) {
			printf("D Released\n");
		}

		object.sprite.move(normalize(move) * movementData.speed * -static_cast<float>(input.controlsInverted * 2 - 1) * dt.asSeconds());
	}
}
