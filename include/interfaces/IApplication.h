#pragma once
#include "managers/AssetManager.h"
#include "managers/StateManager.h"
#include <ui/GUI.h>

enum StatusType;

//Application interface to avoid cylcic header dependency hell
class IApplication {
public:
	virtual StatusType Start() = 0;
	virtual void Stop(StatusType status) = 0;

	bool running{ true };
	sf::RenderWindow window;

	sf::View uiView;
	GUI gui;

	StateManager stateManager{};
	AssetManager assetManager{};
};
