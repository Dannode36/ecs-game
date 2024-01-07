#include "states/MainMenuState.h"
#include "interfaces/IApplication.h"
#include "fmt/format.h"

MainMenuState::MainMenuState(std::string stateID, IApplication& app) : IState(stateID, app) { }

MainMenuState::~MainMenuState() {

}

void MainMenuState::Dispose() {

}

void MainMenuState::Load() {
    texture = app.assetManager.Load<sf::Texture>("assets/button_normal.png");

    button = Button(*texture, *texture, *texture, sf::Vector2f(300, 300));
    button.event.addListener(
        [&](Button& sender) {
            fmt::print("Button(Load Scene, {}) was pressed\n", fmt::ptr(&sender));
            app.stateManager.SetActiveState("Game");
        });
}

void MainMenuState::Reload() {

}

void MainMenuState::HandleEvent(sf::Event& event) {

}

void MainMenuState::Update(sf::Time dt) {
    button.update(app.window.mapPixelToCoords(sf::Mouse::getPosition(app.window)));
}

void MainMenuState::Draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    window.draw(button);
}
