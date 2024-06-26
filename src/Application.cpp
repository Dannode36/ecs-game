#include "Application.h"
#include "fmt/format.h"
#include "states/MainMenuState.h"
#include "states/GameState.h"
#include "states/SplashScreenState.h"
#include <Input.h>
#include <util/TexturePacker.h>

StatusType Application::Start()
{
    {
        std::string msg;
        msg += ">>>>Available Video Modes>>>>>>>\n";
        for (int i = 0; auto& videoMode : sf::VideoMode::getFullscreenModes()) {
            msg += fmt::format("Video mode {0}: Width={1}, Height={2}, Bits per pixel={3}\n", i, videoMode.width, videoMode.height, videoMode.bitsPerPixel);
            i++;
        }
        msg += "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
        spdlog::debug(msg);
    }

    window.create(sf::VideoMode(1280, 800), "Game");
    //window.create(sf::VideoMode::getFullscreenModes()[1], "ImGui + SFML = <3", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    uiView.setSize(sf::Vector2f(window.getSize()));

    ImGui::SFML::Init(window);

    stateManager.RegisterApp(*this);
    //stateManager.AddActiveState(std::shared_ptr<IState>(new SplashScreenState("Splash", *this)));
    stateManager.AddActiveState(std::shared_ptr<IState>(new MainMenuState("Main Menu", *this)));
    stateManager.AddInactiveState(std::shared_ptr<IState>(new GameState("Game", *this)));
    //stateManager.AddActiveState(new GameState("Game", *this));

    {
        std::vector<TileSet> tilesets;
        tilesets.emplace_back("assets/packing_test_1.png", 0, 10);
        tilesets.emplace_back("assets/packing_test_2.png", 10, 8);
        atlas = packTilesets(tilesets, 16U);
    }

    /*try {
        std::vector<TileSet> tilesets;
        tilesets.emplace_back("assets/packing_test_1.png", 0, 10);
        tilesets.emplace_back("assets/packing_test_2.png", 11, 8);
        packTilesets(tilesets, 16U);
    }
    catch (const std::exception& e) {
        LOG_CRITICAL(std::string("A fatal exception occurred: ") + e.what());
    }*/

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
    auto activeState = stateManager.GetActiveState();

    Input::Refresh();

    // Main window event processing
    sf::Event event;
    while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(window, event);

        //Test close event first to early out
        if (event.type == sf::Event::Closed) {
            window.close();
            ImGui::SFML::Shutdown(); // will shutdown all windows
            Stop(StatusAppOK);
            return;
        }

        Input::Update(event); //Update the input abstractions
        activeState->HandleEvent(event); //Allow active state to process the event

        //Engine stuff
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
    if (showImGuiDemoWindow) {
        ImGui::ShowDemoWindow(&showImGuiDemoWindow);
    }

    //Application-wide Debug UI
    static bool assetMgrMetricsOpen = true;
    if (assetMgrMetricsOpen) {
        assetManager.RenderDebugMetricsUI(&assetMgrMetricsOpen);
    }

    static bool metricsOpen = true;
    if (metricsOpen) {
        if (ImGui::Begin("Metrics", &metricsOpen)) {
            fpsGraph.Render("Framerate", 1.f / dt.asSeconds());
            ImGui::NewLine();
            ftGraph.Render("Actual frame time (ms)", static_cast<float>(frameClock.getElapsedTime().asMilliseconds()));
            ImGui::NewLine();
            rtGraph.Render("Total time rendering (us)", static_cast<float>(renderTime.asMicroseconds()));
            ImGui::NewLine();
            wtGraph.Render("Total time waiting (ms)", static_cast<float>(dt.asMilliseconds() - frameClock.getElapsedTime().asMilliseconds()));
        }
        ImGui::End();
    }

    static bool inputOpen = true;
    if (inputOpen) {
        if (ImGui::Begin("Input", &inputOpen)) {
            ImGui::Text(fmt::format("Is any input pressed?: {}", Input::Any()).c_str());
            ImGui::Text(fmt::format("Is any input down?:    {}", Input::AnyDown()).c_str());

            ImGui::NewLine();

            ImGui::Text("Mouse");

            for (size_t i = 0; auto & mouseBtn : Input::mouseButtonStates) {
                ImGui::Text(fmt::format("Is any mouse {} pressed?: {}", i, Input::GetMouseButton(MouseButton(i))).c_str());
                i++;
            }

            for (size_t i = 0; auto & key : Input::keyStates) {
                ImGui::Text(fmt::format("Is any key {} pressed?: {}", keyToString((KeyCode)i), Input::GetKey((KeyCode)i)).c_str());
                i++;
            }
        }
        ImGui::End();
    }

    //Purposeful exception
    if (Input::GetKey(KeyCode::E) && Input::GetKey(KeyCode::LControl)) {
        throw std::exception("Forced exception");
    }
    renderClock.restart();
    //Draw State
    activeState->Draw(window);

    sf::Sprite atlasSprite(*atlas);
    window.draw(atlasSprite);

    //Render
    ImGui::SFML::Render(window);
    renderTime = renderClock.getElapsedTime();
    window.display();

    //Cleanup
    stateManager.Cleanup();
    frameClock.restart();
}
