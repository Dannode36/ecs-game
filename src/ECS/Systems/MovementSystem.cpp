#include "ecs/systems/MovementSystem.h"
#include "ecs/ECS.h"
#include <mathf.h>

extern ECS ecs;

void MovementSystem::Update(const sf::Time& dt)
{
    for (auto const& entity : mEntities) {
        sf::Vector2f move;
        auto& object = ecs.GetComponent<GameObject>(entity);
        auto& movementData = ecs.GetComponent<MovementController>(entity);

        if (Input::GetKey(KeyCode::W)) {
            move.y += -1;
        }
        if (Input::GetKey(KeyCode::A)) {
            move.x += -1;
        }
        if (Input::GetKey(KeyCode::S)) {
            move.y += 1;
        }
        if (Input::GetKey(KeyCode::D)) {
            move.x += 1;
        }

        if (Input::GetKeyDown(KeyCode::W)) {
            printf("W pressed\n");
        }
        if (Input::GetKeyDown(KeyCode::A)) {
            printf("A pressed\n");
        }
        if (Input::GetKeyDown(KeyCode::S)) {
            printf("S pressed\n");
        }
        if (Input::GetKeyDown(KeyCode::D)) {
            printf("D pressed\n");
        }

        if (Input::GetKeyUp(KeyCode::W)) {
            printf("W Released\n");
        }
        if (Input::GetKeyUp(KeyCode::A)) {
            printf("A Released\n");
        }
        if (Input::GetKeyUp(KeyCode::S)) {
            printf("S Released\n");
        }
        if (Input::GetKeyUp(KeyCode::D)) {
            printf("D Released\n");
        }

        object.sprite.move(normalize(move) * movementData.speed * -static_cast<float>(Input::controlsInverted * 2 - 1) * dt.asSeconds());
    }
}
