#include "Application.h"
#include <mathf.h>
#include "fmt/format.h"

ECS ecs;

void Application::InitECS()
{
    ecs.Init();
    ecs.RegisterComponent<GameObject>();
    ecs.RegisterComponent<Collider>();
    ecs.RegisterComponent<Character>();
    ecs.RegisterComponent<MovementController>();

    renderSystem = ecs.RegisterSystem<RenderSystem>();
    Signature renderSignature;
    renderSignature.set(ecs.GetComponentType<GameObject>());
    ecs.SetSystemSignature<RenderSystem>(renderSignature);

    physicsSystem = ecs.RegisterSystem<PhysicsSystem>();
    Signature physicsSignature;
    physicsSignature.set(ecs.GetComponentType<Collider>());
    ecs.SetSystemSignature<PhysicsSystem>(renderSignature);

    movementSystem = ecs.RegisterSystem<MovementSystem>();
    Signature movementSignature;
    movementSignature.set(ecs.GetComponentType<GameObject>());
    movementSignature.set(ecs.GetComponentType<MovementController>());
    ecs.SetSystemSignature<MovementSystem>(movementSignature);

    entities = std::vector<Entity>(MAX_ENTITIES);
}

int Application::Start()
{
    fmt::print("Available Video Modes ->\n");
    int i = 0;
    for (auto& videoMode : sf::VideoMode::getFullscreenModes())
    {
        fmt::print("Video mode {0}: Width={1}, Height={2}, Bits per pixel={3}\n", i, videoMode.width, videoMode.height, videoMode.bitsPerPixel);
        i++;
    }

    //window.create(sf::VideoMode(1280, 800), "ImGui + SFML = <3");
    window.create(sf::VideoMode::getFullscreenModes()[1], "ImGui + SFML = <3", sf::Style::Fullscreen);
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    ImGui::SFML::Init(window);
    gameView.reset(sf::FloatRect(0, 0, 640, 360));

    InitECS();

    entities[0] = ecs.CreateEntity();
    GameObject player;
    auto texture = assetMgr.Load<sf::Texture>("assets/player.png");
    player.sprite.setTexture(*texture);
    player.sprite.setColor(sf::Color(100, 255, 100));
    ecs.AddComponent(entities[0], player);
    ecs.AddComponent(entities[0], Collider{ sf::Vector2f(), 40.0f });
    ecs.AddComponent(entities[0], MovementController{ 40.0f });

    entities[1] = ecs.CreateEntity();
    GameObject enemy;
    auto texture2 = assetMgr.Load<sf::Texture>("assets/player.png");
    enemy.sprite.setTexture(*texture);
    enemy.sprite.setColor(sf::Color(255, 100, 100));
    ecs.AddComponent(entities[1], enemy);
    ecs.AddComponent(entities[1], Collider{ sf::Vector2f(), 40.0f });

    /*auto soundBuffer = assetMgr.Load<sf::SoundBuffer>("assets/wind.ogg");
    sf::Sound wind(*soundBuffer);
    wind.setLoop(true);
    wind.setRelativeToListener(true);
    wind.setVolume(36);
    wind.play();*/

    font.loadFromFile("assets/Roboto-Regular.ttf");
    font.setSmooth(false);

    std::shared_ptr<sf::Texture> buttonNormal = assetMgr.Load<sf::Texture>("assets/button_normal.png");
    std::shared_ptr<sf::Texture> buttonHovered = assetMgr.Load<sf::Texture>("assets/button_hovered.png");
    std::shared_ptr<sf::Texture> buttonPressed = assetMgr.Load<sf::Texture>("assets/button_pressed.png");
    button = Button(*buttonNormal, *buttonHovered, *buttonPressed, sf::Vector2f(300, 300));

    auto music = assetMgr.Load<sf::Music>("assets/wind.ogg");
    music->setLoop(true);
    music->setRelativeToListener(true);
    music->setVolume(36);
    music->play();

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

    //DO NOT USE INPUT MANAGER IN A NEW FRAME BEFORE THIS CALL 
    //Clean key states before updating for this frame. 
    Input::Refresh();

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

    //Update Logic
    const sf::Time dt = deltaClock.restart();
    physicsSystem->Update(dt.asSeconds());
    movementSystem->Update(dt);

    //Draw Debug UI
    ImGui::SFML::Update(window, dt);
    ImGui::SFML::SetCurrentWindow(window);
    ImGui::ShowDemoWindow(&showImGuiDemoWindow);

    assetMgr.RenderDebugMetricsUI(NULL);

    if (ImGui::Begin("Debug")) {
        ImGui::Checkbox("Fade Screen", &fadingScreen);
        ImGui::Checkbox("Fade In", &fadingIn);

        fpsGraph.Render(dt.asSeconds());
    }
    ImGui::End();

    //Draw Game
    window.clear(sf::Color::Black);
    window.setView(gameView);
    renderSystem->DrawEntities(window);

    //Draw Game UI
    //window.setView(window.getDefaultView());
    button.update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    window.draw(button);

    ////Cursor position
    //static sf::RectangleShape rect(sf::Vector2f(4, 4));
    //rect.setFillColor(sf::Color::Black);
    //rect.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    //window.draw(rect);
    window.draw(fade);

    //Render
    ImGui::SFML::Render(window);
    window.display();
}

void Application::Stop()
{
    running = false;
}
