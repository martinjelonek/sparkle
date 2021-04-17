#include "./Game.h"
#include "./Constants.h"
#include "./AssetManager.h"
#include "./Map.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/TextLabelComponent.h"
#include "./Components/ProjectileEmitterComponent.h"
#include "../lib/glm/glm.hpp"
#include <iostream>

using namespace glm;

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    //initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    
    if (TTF_Init() != 0) {
        std::cerr << "Error initializing SDL_TTF" << std::endl;
        return;
    }

    //create SDL window
    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);    
    if(!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
    }

    LoadLevel(0);

    isRunning = true;
    return;
}

Entity& player(manager.AddEntity("wildhammer-image", PLAYER_LAYER));

void Game::LoadLevel(int levelNumber) {
    //Adding new assets to the assetmanager list (map)
    assetManager->AddTexture("catapult-image", std::string("./assets/images/catapult-big-right.png").c_str());
    assetManager->AddTexture("wildhammer-image", std::string("./assets/images/wildhammer.png").c_str());
    assetManager->AddTexture("fields-tiletexture", std::string("./assets/tilemaps/fields.png").c_str());
    assetManager->AddTexture("enemy-projectile", std::string("./assets/images/enemy-projectile.png").c_str());
    assetManager->AddFont("pixeldown-font", std::string("./assets/fonts/pixeldown.ttf").c_str(), 14);

    map = new Map("fields-tiletexture", 2, 32);
    map->LoadMap("./assets/tilemaps/fields.map", 25, 20);

    //Adding entities with components
    player.AddComponent<TransformComponent>(150, 10, 0, 0, 32, 32, 1);
    player.AddComponent<SpriteComponent>("wildhammer-image", 2, 360, true, false);
    player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
    player.AddComponent<ColliderComponent>("player", 150, 10, 32, 32);

    Entity& catapultEntity(manager.AddEntity("catapult", ENEMY_LAYER));
    catapultEntity.AddComponent<TransformComponent>(150, 495, 20, -5, 32, 32, 1);
    catapultEntity.AddComponent<SpriteComponent>("catapult-image");
    catapultEntity.AddComponent<ColliderComponent>("enemy", 150, 495, 32, 32);

    Entity& projectile(manager.AddEntity("projectile", PROJECTILE_LAYER));
    projectile.AddComponent<TransformComponent>(150+16, 495+16, 0, 0, 4, 4, 1);
    projectile.AddComponent<SpriteComponent>("enemy-projectile");
    projectile.AddComponent<ColliderComponent>("projectile", 150+16, 495+16, 4, 4);
    projectile.AddComponent<ProjectileEmitterComponent>(50, 270, 200, true);

    Entity& labelGameTitle(manager.AddEntity("LabelGameTitle", UI_LAYER));
    labelGameTitle.AddComponent<TextLabelComponent>(10, 10, "Wildhammer", "pixeldown-font", WHITE_COLOR);

    #ifdef DEBUG
        std::cout << "Game::LoadLevel: " << levelNumber << " complete. Result:" << std::endl;
        manager.ListAllEntities();
    #endif
}

void Game::ProcessInput() {
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        if(event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
    default:
        break;
    }
}

void Game::Update() {
    //sleep the execution until reach the target frame time (ms)
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

    //delay if needed
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) SDL_Delay(timeToWait);

    //delta time - difference in ticks from last frame in ms
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    //clamp deltaTime to the max value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    
    //set current ticks for the next update
    ticksLastFrame = SDL_GetTicks();

    //update
    manager.Update(deltaTime);
    HandleCameraMovement();
    CheckCollisions();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) return;
    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement () {
    TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();

    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions () {
    manager.CheckCollisions(isRunning);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}