#include "Application.h"

ECS ecs;

void Application::InitECS()
{
    ecs.Init();
    ecs.RegisterComponent<Transform>();
    ecs.RegisterComponent<RigidBody>();
    ecs.RegisterComponent<Renderer>();

    Signature physicsSignature;
    physicsSignature.set(ecs.GetComponentType<Transform>());
    physicsSignature.set(ecs.GetComponentType<RigidBody>());

    Signature renderSignature;
    renderSignature.set(ecs.GetComponentType<Transform>());
    renderSignature.set(ecs.GetComponentType<Renderer>());

    physicsSystem = ecs.RegisterSystem<PhysicsSystem>();
    ecs.SetSystemSignature<PhysicsSystem>(physicsSignature);

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
    ecs.AddComponent(entities[0], Renderer{});
    ecs.AddComponent(entities[0], Transform{ Vector2{50, 50} });
    ecs.AddComponent(entities[0], RigidBody{ 2, Vector2{10.0, 10.0 } });

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
    physicsSystem->Update(dt.asSeconds());

    //Setup UI
    ImGui::SFML::Update(window, dt);
    ImGui::SFML::SetCurrentWindow(window);
    ImGui::ShowDemoWindow(&showImGuiDemoWindow);

    //Draw Game
    window.clear();
    renderSystem->DrawEntities(window);
    
    //Draw UI and display window
    ImGui::SFML::Render(window);
    window.display();
}

void Application::Stop()
{
    running = false;
}
