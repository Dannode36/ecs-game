#include "states/GameState.h"
#include <fmt/format.h>
#include <mathf.h>
#include "interfaces/IApplication.h"

ECS ecs;

GameState::GameState(const std::string stateID, IApplication& app) : IState(stateID, app) { }

GameState::~GameState(){
    Dispose();
}

void GameState::Dispose() {
    wind.reset();
    playerTexture.reset();
}

void GameState::InitECS()
{
    ecs.Init();
    ecs.RegisterComponent<GameObject>();
    ecs.RegisterComponent<Camera>();
    ecs.RegisterComponent<Collider>();
    ecs.RegisterComponent<Character>();
    ecs.RegisterComponent<MovementController>();
    ecs.RegisterComponent<Enemy>();
    ecs.RegisterComponent<Projectile>();

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

    enemySystem = ecs.RegisterSystem<EnemySystem>();
    Signature enemySignature;
    enemySignature.set(ecs.GetComponentType<GameObject>());
    enemySignature.set(ecs.GetComponentType<Enemy>());
    ecs.SetSystemSignature<EnemySystem>(enemySignature);

    cameraSystem = ecs.RegisterSystem<CameraSystem>();
    Signature cameraSignature;
    cameraSignature.set(ecs.GetComponentType<Camera>());
    ecs.SetSystemSignature<CameraSystem>(cameraSignature);

    entities = std::vector<Entity>(MAX_ENTITIES);
}

void GameState::Load() {
    sf::Clock timer;
    IState::Load();

    view.reset(sf::FloatRect(0, 0, 640, 360));
    timer.restart();
    InitECS();

    backgroundTexture = app.assetManager.Load<sf::Texture>("assets/Textures-16.png");
    background.setTexture(*backgroundTexture);

    playerTexture = app.assetManager.Load<sf::Texture>("assets/player.png");
    enemySystem->Init(playerTexture);

    entities[0] = ecs.CreateEntity();
    GameObject player;
    player.sprite.setTexture(*playerTexture);
    player.sprite.setColor(sf::Color(100, 255, 100));
    ecs.AddComponent(entities[0], player);
    ecs.AddComponent(entities[0], Collider{ sf::Vector2f(), 40.0f });
    ecs.AddComponent(entities[0], MovementController{ 40.0f });
    this->player = &ecs.GetComponent<GameObject>(entities[0]); //Get a reference back to the player for future use

    entities[1] = ecs.CreateEntity();
    Camera camera(view, 2.f);
    ecs.AddComponent(entities[1], camera);

    entities[2] = ecs.CreateEntity();
    GameObject enemy;
    enemy.sprite.setTexture(*playerTexture);
    enemy.sprite.setColor(sf::Color(255, 100, 100));
    ecs.AddComponent(entities[2], enemy);
    ecs.AddComponent(entities[2], Collider{ sf::Vector2f(), 40.0f });

    enemySystem->Init(playerTexture);

    /*auto soundBuffer = assetMgr.Load<sf::SoundBuffer>("assets/wind.ogg");
    sf::Sound wind(*soundBuffer);
    wind.setLoop(true);
    wind.setRelativeToListener(true);
    wind.setVolume(36);
    wind.play();*/

    TexturePtr buttonNormal = app.assetManager.Load<sf::Texture>("assets/button_normal.png");
    TexturePtr buttonHovered = app.assetManager.Load<sf::Texture>("assets/button_hovered.png");
    TexturePtr buttonPressed = app.assetManager.Load<sf::Texture>("assets/button_pressed.png");

    button = Button(buttonNormal, buttonHovered, buttonPressed, sf::Vector2f(300, 300));
    button.event.addListener(
        [&](Button& sender) {
            fmt::print("Button(Load Scene, {}) was pressed\n", fmt::ptr(&sender));
            app.stateManager.SetActiveState("Main Menu");
        });

    button2 = Button(buttonNormal, buttonHovered, buttonPressed, sf::Vector2f(200, 300));
    button2.event.addListener(
        [&](Button& sender) {
            fmt::print("Button(Unload Scene, {}) was pressed\n", fmt::ptr(&sender));
            app.stateManager.DropActiveState();
        });

    f = std::async(std::launch::async, [&]() {
        wind = app.assetManager.LoadAsync<sf::Music>("assets/wind.ogg").get();
        wind->setLoop(true);
        wind->setRelativeToListener(true);
        wind->setVolume(36);
        wind->play();
    });

    fade.setPosition(sf::Vector2f(0, 0));
    fade.setFillColor(sf::Color(0, 0, 0, 0));
}

void GameState::Reload() {
    //view.reset(sf::FloatRect(0, 0, 640, 360));
    app.window.setView(view);
    wind->stop();
    wind->play();
}

void GameState::Pause() {
    IState::Pause();
    if (IsLoaded()) {
        wind->stop();
    }
}

void GameState::Resume() {
    IState::Resume();
    if (IsLoaded()) {
        wind->play();
    }
}

void GameState::HandleEvent(sf::Event& event) {

}

void GameState::Update(sf::Time dt) {
    if (fadingScreen) {
        fade.setSize(sf::Vector2f(app.window.getSize()));

        currentTime += dt.asMilliseconds();
        if (currentTime < targetTime) {
            if (fadingIn) {
                fade.setFillColor(sf::Color(0, 0, 0, lerp(startAlpha, endAlpha, currentTime / (float)targetTime)));
            }
            else {
                fade.setFillColor(sf::Color(0, 0, 0, lerp(endAlpha, startAlpha, currentTime / (float)targetTime)));
            }
        }
        else {
            fadingScreen = false;
            currentTime = 0;
        }
        printf("current time %d\n", currentTime);
    }

    physicsSystem->Update(dt.asSeconds());
    movementSystem->Update(dt);
    enemySystem->Update(dt, entities[0]);

    //Update last
    cameraSystem->Update(dt, player->sprite.getPosition());

    auto mouseGlobalPos = app.window.mapPixelToCoords(sf::Mouse::getPosition(app.window));
    button.update(mouseGlobalPos);
    button2.update(mouseGlobalPos);
}

void GameState::Draw(sf::RenderWindow& window) {
    app.window.setView(view);


    //Draw Debug UI
    if (ImGui::Begin("Debug")) {
        ImGui::Checkbox("Fade Screen", &fadingScreen);
        ImGui::Checkbox("Fade In", &fadingIn);
    }
    ImGui::End();

    //Draw Game
    window.clear(sf::Color::Black);
    window.draw(background);

    //window.setView(window.getDefaultView());
    renderSystem->DrawEntities(window);

    //Draw Game UI
    //window.setView(app.uiView);
    window.draw(button);
    window.draw(button2);
}
