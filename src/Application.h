#pragma once
//Do not change order
#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"

#ifndef SPDLOG_FMT_EXTERNAL
    #define SPDLOG_FMT_EXTERNAL
#endif
#include "vendor/spdlog/spdlog.h"

#include "interfaces/IApplication.h"
#include <ui/imgui/MetricGraph.h>

class Application : IApplication
{
public:
    Application() = default;

    StatusType Start();
    void Stop(StatusType status);
    void Update();

private:
    //Window
    StatusType status = StatusNoError;
    sf::Clock deltaClock{};

    std::shared_ptr<sf::Texture> atlas;

    //Debug UI
    sf::Clock frameClock{};
    MetricGraph fpsGraph{};
    MetricGraph ftGraph{};
    MetricGraph wtGraph{};
    bool showImGuiDemoWindow{ false };
};
