#include "./Game.h"
#include "./Constants.h"
#include "./AssetManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "../lib/glm/glm.hpp"
#include <iostream>

using namespace glm;
using namespace std;

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

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
        cerr << "Error initializing SDL." << endl;
        return;
    }
    
    //create SDL window
    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);    
    if(!window) {
        cerr << "Error creating SDL window." << endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) {
        cerr << "Error creating SDL renderer." << endl;
    }

    LoadLevel(0);

    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber) {
    //Adding new assets to the assetmanager list (map)
    assetManager->AddTexture("catapult-image", string("./assets/images/catapult-big-right.png").c_str());
    assetManager->AddTexture("wildhammer-image", string("./assets/images/wildhammer.png").c_str());

    //Adding entities with components
    Entity& catapultEntity(manager.AddEntity("catapult"));
    catapultEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    catapultEntity.AddComponent<SpriteComponent>("catapult-image");

    Entity& wildhammerEntity(manager.AddEntity("wildhammer-image"));
    wildhammerEntity.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    wildhammerEntity.AddComponent<SpriteComponent>("wildhammer-image", 2, 360, true, false);

    #ifdef DEBUG
        cout << "Game::LoadLevel: " << levelNumber << " complete. Result:" << endl;
        manager.ListAllEntities();
    #endif
}

void Game::ProcessInput() {
    SDL_Event event;
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

    //Clamp deltaTime to the max value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    
    //set current ticks for the next update
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) return;
    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}