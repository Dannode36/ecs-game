#pragma once
#include "interfaces/IState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <ui/Button.h>

class MainMenuState : public IState
{
private:
	TexturePtr texture;
	Button button{};


public:
	MainMenuState(std::string stateID, IApplication& app);
	~MainMenuState();

	// Inherited via IState
	void Load() override;
	void Reload() override;
	void HandleEvent(sf::Event& event) override;
	void Update(sf::Time dt) override;
	void Draw(sf::RenderWindow& target) override;

private:
	void Dispose() override;
};
