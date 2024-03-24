#include "ecs/systems/EnemySystem.h"
#include <ecs/ECS.h>
#include <mathf.h>
#include <SFML/System/Time.hpp>

extern ECS ecs;

void EnemySystem::Init(TexturePtr enemyTexture) {
	this->enemyTexture = enemyTexture;
}

void EnemySystem::Update(sf::Time& dt, Entity player) {
	auto& playerObject = ecs.GetComponent<GameObject>(player);
	auto& playerData = ecs.GetComponent<Character>(player);

	std::vector<Entity> deadEnemies;
	for (auto& enemy : mEntities) {
		auto& gameObject = ecs.GetComponent<GameObject>(enemy);
		auto& enemyData = ecs.GetComponent<Enemy>(enemy);

		//Move towards the player
		sf::Vector2f directionToPlayer = playerObject.getPosition() - gameObject.getPosition();
		gameObject.move(normalize(directionToPlayer) * enemyData.speed * dt.asSeconds());

		//Check if collided with player yet
		if (playerObject.getGlobalBounds().intersects(gameObject.getGlobalBounds())) {
			playerData.health -= 1;
		}
	}

	//Remove dead enemies
	for (auto& dead : deadEnemies) {
		mEntities.erase(dead);
		ecs.DestroyEntity(dead);
	}

	//Spawn new enemies
	if (spawnedCount < spawnCount) {
		StartWave();
		if (spawnDelay <= spawnClock.getElapsedTime().asSeconds()) {
			//Spawn enemy
			SpawnEnemy(Enemy{ 10.f, 1 });
			spawnedCount++;
			spawnClock.restart();
		}
	}
}

void EnemySystem::StartWave() {
	waveCounter++;
	spawnCount = (waveCounter * waveCounter * 0.4f) + 5;
}

/*
	\brief Enemy data:
	\brief Regular = 10u/s, 1hp
	\brief Speedy = 20u/s, 1hp
	\brief Huge = 5u/s, 5hp
*/
void EnemySystem::SpawnEnemy(Enemy enemyData) {
	Entity enemy = ecs.CreateEntity();
	GameObject enemyObject;
	enemyObject.setTexture(*enemyTexture);
	ecs.AddComponent(enemy, enemyObject);
	ecs.AddComponent(enemy, enemyData);
}
