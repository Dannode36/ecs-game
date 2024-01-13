#pragma once
#include "interfaces/IState.h"
#include <SFML/Graphics/RenderWindow.hpp>

class SplashScreenState : public IState
{
public:
	SplashScreenState(std::string stateID, IApplication& app);
	~SplashScreenState();

	// Inherited via IState
	void Dispose() override;
	void Reload() override;
	void HandleEvent(sf::Event& checkEvent) override;
	void Update(sf::Time dt) override;
	void Draw(sf::RenderWindow& target) override;
};

