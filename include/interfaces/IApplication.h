#pragma once
#include "managers/AssetManager.h"
#include "managers/StateManager.h"

enum StatusType;

//Application interface to avoid cylcic header dependency hell
class IApplication {
public:
	virtual StatusType Start() = 0;
	virtual void Stop(StatusType status) = 0;

	bool running{ true };
	sf::RenderWindow window;

	AssetManager assetManager{};
	StateManager stateManager{};
};
