#pragma once
#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>

#include "interfaces/IState.h"
#include <managers/AssetManager.h>
#include <ui/imgui/MetricGraph.h>
#include <ui/Button.h>
#include <ecs/ECS.h>
#include <ecs/systems/EnemySystem.h>
#include <ecs/systems/CameraSystem.h>
#include <game/TileMap.h>

class GameState : public IState
{
private:
    //Rendering
    sf::View view;

    //Game Data
    TileMap tileMap;

    //ECS
    std::vector<Entity> entities;
    std::shared_ptr<PhysicsSystem> physicsSystem;
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<MovementSystem> movementSystem;
    std::shared_ptr<EnemySystem> enemySystem;
    std::shared_ptr<CameraSystem> cameraSystem;
    std::future<void> f;

    GameObject* player;
    //UI
    Button button;
    Button button2;

    sf::Sprite background;
    //eventually
    //GUI gui;

    sf::RectangleShape fade;
    bool fadingScreen = false;
    bool fadingIn = true;
    int startAlpha = 255;
    int endAlpha = 0;
    int targetTime = 2500;
    int currentTime = 0;

    //Assets
    MusicPtr wind;
    TexturePtr playerTexture;
    TexturePtr backgroundTexture;
public:
    GameState(const std::string stateID, IApplication& app);
    ~GameState();
    // Inherited via IState
    void Load() override;
    void Reload() override;
    void Pause() override;
    void Resume() override;
    void HandleEvent(sf::Event& event) override;
    void Update(sf::Time dt) override;
    void Draw(sf::RenderWindow& window) override;

private:
    void Dispose() override;
    void InitECS();
};
