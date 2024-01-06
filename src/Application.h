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
#include "ECS/ECS.h"
#include "assetManager/AssetManager.h"
#include "Input.h"
#include "ui/Button.h"
#include "ui/FpsGraph.h"

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

    sf::RectangleShape fade;
    bool fadingScreen{ false };
    bool fadingIn{ true };
    int startAlpha = 255;
    int endAlpha = 0;
    int targetTime = 2500;
    int currentTime;
public:
    int Start();

private:
    void InitECS();
    void Update();
    void Stop();
public:

    Application() = default;
};
