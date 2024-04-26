#pragma once
#include "interfaces/IState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class SplashScreenState : public IState
{
public:
	SplashScreenState(std::string stateID, IApplication& app);
	~SplashScreenState();

	// Inherited via IState
	void Dispose() override;
	void Load() override;
	void Pause() override;
	void Update(sf::Time dt) override;
	void Draw(sf::RenderWindow& target) override;
private:
	sf::RenderWindow window;
	sf::Vector2u originalWindowSize;
	sf::Texture splashImage;
	sf::Sprite splashSprite;
	const int showTime = 5000; //milliseconds
	int currentTime = 0;

	// Inherited via IState
	void Reload() override;
	void HandleEvent(sf::Event& event) override;
};
