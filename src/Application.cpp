#include "Application.h"
#include <mathf.h>

ECS ecs;

void Application::InitECS()
{
    ecs.Init();
    ecs.RegisterComponent<GameObject>();
    ecs.RegisterComponent<Character>();

    Signature renderSignature;
    renderSignature.set(ecs.GetComponentType<GameObject>());

    renderSystem = ecs.RegisterSystem<RenderSystem>();
    ecs.SetSystemSignature<RenderSystem>(renderSignature);

    entities = std::vector<Entity>(MAX_ENTITIES);
}

int Application::Start()
{
    window.create(sf::VideoMode(1280, 720), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    InitECS();

    entities[0] = ecs.CreateEntity();
    GameObject player;
    auto texture = assetmgr.textureCache.Load("assets/player.png");
    player.sprite.setTexture(*texture);
    ecs.AddComponent(entities[0], player);

    auto soundBuffer = assetmgr.soundCache.Load("assets/wind.ogg");
    sf::Sound wind(*soundBuffer);
    wind.setLoop(true);
    wind.setRelativeToListener(true);
    wind.setVolume(36);
    wind.play();

    fade.setPosition(sf::Vector2f(0, 0));
    fade.setFillColor(sf::Color(0, 0, 0, 0));

    deltaClock.restart();
    while (running) {
        Update();
    }

    Stop();
    return 0;
}

void Application::Update()
{
    if (fadingScreen) {
        fade.setSize(sf::Vector2f(window.getSize()));

        currentTime += deltaClock.getElapsedTime().asMilliseconds();
        if (currentTime < targetTime) {
            if (fadingIn) {
                fade.setFillColor(sf::Color(0, 0, 0, lerp(startAlpha, endAlpha, currentTime / (float)targetTime)));
            }
            else
            {
                fade.setFillColor(sf::Color(0, 0, 0, lerp(endAlpha, startAlpha, currentTime / (float)targetTime)));
            }
        }
        else {
            fadingScreen = false;
            currentTime = 0;
        }
        printf("current time %d\n", currentTime);
    }

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
    //physicsSystem->Update(dt.asSeconds());

    //Draw UI
    ImGui::SFML::Update(window, dt);
    ImGui::SFML::SetCurrentWindow(window);
    ImGui::ShowDemoWindow(&showImGuiDemoWindow);

    assetmgr.RenderDebugMetricsUI(NULL);

    if (ImGui::Begin("Debug")) {
        ImGui::Checkbox("Fade Screen", &fadingScreen);
        ImGui::Checkbox("Fade In", &fadingIn);
    }
    ImGui::End();

    //Draw Game
    window.clear(sf::Color(255, 255, 255, 255));
    renderSystem->DrawEntities(window);
    window.draw(fade);

    //Draw all to window
    ImGui::SFML::Render(window);
    window.display();
}

void Application::Stop()
{
    running = false;
}
