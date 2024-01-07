#pragma once
#include "interfaces/IState.h"
#include <SFML/Graphics/RenderWindow.hpp>

class MainMenuState : public IState
{
public:
	MainMenuState(std::string stateID, IApplication& app);
	~MainMenuState();

	// Inherited via IState
	void Dispose() override;
	void Reload() override;
	void HandleEvent(sf::Event& event) override;
	void Update(sf::Time dt) override;
	void Draw(sf::RenderWindow& target) override;
};

