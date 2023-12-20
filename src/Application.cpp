#include "Application.h"

ECS gECS;

int Application::Start()
{
    window.create(sf::VideoMode(1280, 720), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::Time elapsed_time;

    while (running) {
        Update();
    }

    Stop();
    return 0;
}

void Application::Update()
{
    static sf::Clock deltaClock;
    // Main window event processing
    sf::Event event;
    while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(window, event);
        if (event.type == sf::Event::Closed) {
            window.close();
            ImGui::SFML::Shutdown(); // will shutdown all windows
            Stop();
            return;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::D && event.key.control && event.key.alt) {
                showImGuiDemoWindow = !showImGuiDemoWindow;
            }
        }
    }

    // Update
    const sf::Time dt = deltaClock.restart();
    ImGui::SFML::Update(window, dt);

    //Render UI
    ImGui::SFML::SetCurrentWindow(window);

    ImGui::ShowDemoWindow(&showImGuiDemoWindow);
    window.clear();
    //window.draw(shape);
    ImGui::SFML::Render(window);
    window.display();
}

void Application::Stop()
{
    running = false;
}
