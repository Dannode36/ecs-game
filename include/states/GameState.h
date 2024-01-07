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
#include <ui/FpsGraph.h>
#include <ui/Button.h>
#include <ecs/ECS.h>

class GameState : public IState
{
private:
    //Rendering
    sf::View view;

    //ECS
    std::vector<Entity> entities;
    std::shared_ptr<PhysicsSystem> physicsSystem;
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<MovementSystem> movementSystem;

    //UI
    Button button;
    Button button2;

    sf::RectangleShape fade;
    bool fadingScreen{ false };
    bool fadingIn{ true };
    int startAlpha = 255;
    int endAlpha = 0;
    int targetTime = 2500;
    int currentTime = 0;


    //Assets
    MusicPtr wind;
    TexturePtr playerTexture;
    TexturePtr buttonNormal;
    TexturePtr buttonHovered;
    TexturePtr buttonPressed;

public:
    GameState(const std::string stateID, IApplication& app);
    ~GameState();
    // Inherited via IState
    void Load() override;
    void Reload() override;
    void HandleEvent(sf::Event& event) override;
    void Update(sf::Time dt) override;
    void Draw(sf::RenderWindow& window) override;

private:
    void Dispose() override;
    void InitECS();
};