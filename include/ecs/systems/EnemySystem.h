#pragma once
#include "ecs/systems/System.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <managers/AssetManager.h>
#include "ecs/Components.h"

class EnemySystem : public System
{
public:
	void Init(TexturePtr enemyTexture);
	void Update(sf::Time& dt, Entity player);
	void StartWave();

private:
	void SpawnEnemy(Enemy enemyData);
	
	//l sour y //Wordscapes notes
	TexturePtr enemyTexture;

	sf::Clock spawnClock;

	int waveCounter = 0;

	int spawnedCount = 0;
	int spawnCount = 5;
	float spawnDelay = 1.f;
};
