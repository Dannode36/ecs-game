#include "states/SplashScreenState.h"
#include <FilePaths.h>
#include "interfaces/IApplication.h"
#include <util/Logging.h>

SplashScreenState::SplashScreenState(std::string stateID, IApplication& app) : IState(stateID, app) { }

SplashScreenState::~SplashScreenState() { }

void SplashScreenState::Dispose() { }

void SplashScreenState::Load() {
	IState::Load();

	//Reset window styles
	originalWindowSize = app.window.getSize();
	//app.window.setSize(sf::Vector2u(0, 0));

	window.create(sf::VideoMode(500, 500), "game", sf::Style::None);
	window.setFramerateLimit(60);
	window.setActive();

	// center the window
	sf::Vector2i splashOrig = {
	   int(sf::VideoMode::getDesktopMode().width) / 2 - int(window.getSize().x) / 2,
	   int(sf::VideoMode::getDesktopMode().height) / 2 - int(window.getSize().y) / 2
	};
	window.setPosition(splashOrig);

	if (!splashImage.loadFromFile(SPLASH_IMAGE)) {
		app.Stop(StatusAppMissingAsset);
		LOG_CRITICAL("Could not load splash image");
	}

	splashSprite.setTexture(splashImage);

	//Draw image
	window.draw(splashSprite);
	window.display();
}

void SplashScreenState::Pause() {
	app.window.setSize(originalWindowSize);
	app.window.setActive();
	window.close();
}

void SplashScreenState::Update(sf::Time dt) {
	currentTime += dt.asMilliseconds();

	if (currentTime >= showTime) {
		app.stateManager.DropActiveState();
	}
}

void SplashScreenState::Draw(sf::RenderWindow& target) { }

void SplashScreenState::Reload() { }

void SplashScreenState::HandleEvent(sf::Event& event) { }
