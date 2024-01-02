#pragma once
#include <vector>

//Do not change order
#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "ECS/ECS.h"
#include "assetManager/AssetManager.h"

class Application
{
private:
    bool running{ true };
    sf::RenderWindow window;
    sf::Clock deltaClock;


    //Assets
    AssetManager assetmgr;

    //ECS
    std::vector<Entity> entities;
    //std::shared_ptr<PhysicsSystem> physicsSystem;
    std::shared_ptr<RenderSystem> renderSystem;

    //Misc
    bool showImGuiDemoWindow{ false };

    sf::RectangleShape fade;
    bool fadingScreen{ true };
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
};
