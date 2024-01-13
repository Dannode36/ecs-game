#include "Application.h"
#include "fmt/format.h"
#include "states/MainMenuState.h"
#include "states/GameState.h"
#include <Input.h>

StatusType Application::Start()
{
    fmt::print("----Available Video Modes ->----\n");
    int i = 0;
    for (auto& videoMode : sf::VideoMode::getFullscreenModes()) {
        fmt::print("Video mode {0}: Width={1}, Height={2}, Bits per pixel={3}\n", i, videoMode.width, videoMode.height, videoMode.bitsPerPixel);
        i++;
    }
    fmt::print("--------------------------------\n");

    window.create(sf::VideoMode(1280, 800), "ECS Game");
    //window.create(sf::VideoMode::getFullscreenModes()[1], "ImGui + SFML = <3", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    uiView.setSize(sf::Vector2f(window.getSize()));

    ImGui::SFML::Init(window);

    stateManager.RegisterApp(this);
    stateManager.AddInactiveState(new GameState("Game", *this));
    stateManager.AddActiveState(new MainMenuState("Main Menu", *this));
    //stateManager.AddActiveState(new GameState("Game", *this));

    while (running && !stateManager.IsEmpty()) {
        Update();
    }
    return status;
}

void Application::Stop(StatusType status)
{
    this->status = status;
    running = false;
}

void Application::Update() {
    IState* activeState = stateManager.GetActiveState();

    Input::Refresh();

    // Main window event processing
    sf::Event event;
    while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(window, event);

        activeState->HandleEvent(event); //Allow active state to process the event

        if (event.type == sf::Event::Closed) {
            window.close();
            ImGui::SFML::Shutdown(); // will shutdown all windows
            Stop(StatusAppOK);
            return;
        }
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
            Input::UpdateKeyState(event);
        }
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
            Input::UpdateMouseState(event);
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::D && event.key.control && event.key.alt) {
                showImGuiDemoWindow = !showImGuiDemoWindow;
            }
        }
    }

    sf::Time dt = deltaClock.restart();
    activeState->Update(dt);

    //Update ImGui
    ImGui::SFML::Update(window, dt);
    ImGui::SFML::SetCurrentWindow(window);
    ImGui::ShowDemoWindow(&showImGuiDemoWindow);

    //Application-wide Debug UI
    assetManager.RenderDebugMetricsUI(NULL);

    if (ImGui::Begin("Metrics")) {
        fpsGraph.Render("Framerate", 1.f / dt.asSeconds());
        ImGui::NewLine();
        ftGraph.Render("Actual frame time (ms)", static_cast<float>(frameClock.getElapsedTime().asMilliseconds()));
        ImGui::NewLine();
        wtGraph.Render("Total time waiting (ms)", static_cast<float>(dt.asMilliseconds() - frameClock.getElapsedTime().asMilliseconds()));
    }
    ImGui::End();

    //Draw State
    activeState->Draw(window);

    //Render
    ImGui::SFML::Render(window);
    window.display();
    frameClock.restart();
}
