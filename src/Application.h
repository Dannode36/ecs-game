#pragma once
#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include "ECS/ECS.h"

class Application
{
private:
    sf::RenderWindow window;
    bool running{ true };

    bool showImGuiDemoWindow{ false };
    std::vector<Entity> entities;
    std::shared_ptr<PhysicsSystem> physicsSystem;
    std::shared_ptr<RenderSystem> renderSystem;
public:
    int Start();

private:
    void InitECS();
    void Update();
    void Stop();
};
