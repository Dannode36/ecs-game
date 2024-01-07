#pragma once
#include <vector>

//Do not change order
#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include "ecs/ECS.h"
#include "managers/AssetManager.h"
#include "Input.h"
#include "ui/Button.h"
#include "ui/FpsGraph.h"
#include <types.h>

class Application
{
private:
    bool running{ true };
    sf::RenderWindow window;
    sf::View gameView;
    sf::Clock deltaClock;
    FPSGraph fpsGraph;

    //Assets
    AssetManager assetMgr;
    sf::Font font;

    //ECS
    std::vector<Entity> entities;
    std::shared_ptr<PhysicsSystem> physicsSystem;
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<MovementSystem> movementSystem;

    //Misc
    bool showImGuiDemoWindow{ false };

    Button button;
    Button button2;

    sf::RectangleShape fade;
    bool fadingScreen{ false };
    bool fadingIn{ true };
    int startAlpha = 255;
    int endAlpha = 0;
    int targetTime = 2500;
    int currentTime = 0;
public:
    int Start();
    void Update();
    void Stop(StatusType status);

private:
    void InitECS();
public:

    Application() = default;
};
