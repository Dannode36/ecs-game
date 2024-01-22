#include "states/MainMenuState.h"
#include "interfaces/IApplication.h"
#include "fmt/format.h"

MainMenuState::MainMenuState(std::string stateID, IApplication& app) : IState(stateID, app) { }

MainMenuState::~MainMenuState() {

}

void MainMenuState::Dispose() {

}

void MainMenuState::Load() {
    IState::Load();

    view.reset(sf::FloatRect(0, 0, 640, 360));
    app.window.setView(view);

    TexturePtr texture = app.assetManager.Load<sf::Texture>("assets/button_normal.png");

    button = Button(texture, texture, texture, sf::Vector2f(300, 300));
    button.event.addListener(
        [&](Button& sender) {
            fmt::print("Button(Load Scene, {}) was pressed\n", fmt::ptr(&sender));
            app.stateManager.SetActiveState("Game");
        });

    TexturePtr checkboxNormal = app.assetManager.Load<sf::Texture>("assets/checkbox_normal.png");
    TexturePtr checkboxHovered = app.assetManager.Load<sf::Texture>("assets/checkbox_hovered.png");
    TexturePtr checkboxCheck = app.assetManager.Load<sf::Texture>("assets/checkbox_check.png");

    checkbox = Checkbox(checkboxNormal, checkboxHovered, checkboxCheck, sf::Vector2f(200, 300));
    checkbox.checkEvent.addListener(
        [&](bool checked) {
            fmt::print("Checkbox was clicked and checked is now {}\n", checked);
        });
    checkbox.hoverEvent.addListener(
        [&](bool hovered) {
            if (hovered) {
                fmt::print("Checkbox is hovered\n");
            }
            else {
                fmt::print("Checkbox is no longer hovered\n");
            }
        });
}

void MainMenuState::Reload() {
   Load();
}

void MainMenuState::HandleEvent(sf::Event& event) {

}

void MainMenuState::Update(sf::Time dt) {
    sf::Vector2f mouseWorldPos = app.window.mapPixelToCoords(sf::Mouse::getPosition(app.window));
    button.update(mouseWorldPos);
    //checkbox.update(mouseWorldPos);
}

void MainMenuState::Draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    //UI
    //window.setView(app.uiView);
    window.draw(button);
    window.draw(checkbox);
}
