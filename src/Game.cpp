#include "./Game.h"
#include "./Constants.h"
#include "./AssetManager.h"
#include "./EventManager.h"
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
EventManager eventManager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Entity* player = NULL;
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

    LoadLevel(1);

    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber) {
    //Lua preparation
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

    std::string levelName = "Level" + std::to_string(levelNumber);
    lua.script_file("./assets/scripts/" + levelName + ".lua");

    sol::table levelData = lua[levelName];
    
    /****************************************************/
    /* LOADING ASSETS FORM LUA CONFIG FILE              */
    /****************************************************/

    sol::table levelAssets = levelData["assets"];   
    unsigned int assetsIndex = 0;
    while(true) {
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetsIndex];
        if (existsAssetIndexNode == sol::nullopt) {
            break;
        } else {
            sol::table asset = levelAssets[assetsIndex];
            std::string assetType = asset["type"];
            if (assetType.compare("texture") == 0) {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                assetManager->AddTexture(assetId, assetFile.c_str());
                #ifdef DEBUG
                    std::cout << "SOL ADDED ASSET: assetType = " << assetType << ", assetId = " << assetId << ", assetFile = " << assetFile << std::endl;
                #endif
            } //else if (assetType.compare("font") == 0) {
                //std::string assetId = asset["id"];
                //std::string assetFile = asset["file"];
                //std::string assetFontSize = asset["fontSize"];
                //assetManager->AddFont(assetId, assetFile.c_str(), assetFontSize);
            //}
            assetsIndex++;
        }
    }

    /****************************************************/
    /* LOADING MAPS FORM LUA CONFIG FILE                */
    /****************************************************/

    sol::table levelMap = levelData["map"];
    std::string mapTextureId = levelMap["textureAssetId"];
    std::string mapFile = levelMap["file"];

    map = new Map{
        mapTextureId,
        static_cast<int>(levelMap["scale"]),
        static_cast<int>(levelMap["tileSize"])
    };

    map->LoadMap (
        mapFile, 
        static_cast<int>(levelMap["mapSizeX"]),
        static_cast<int>(levelMap["mapSizeY"])
    );

    #ifdef DEBUG
        std::string text = "";
        std::cout << "SOL ADDED MAP: mapTextureId = " << mapTextureId << ", mapFile = " << mapFile;
        text = levelMap["scale"];
        std::cout << ", scale = " << text;
        text = levelMap["tileSize"];
        std::cout << ", tileSize = " << text;
        text = levelMap["mapSizeX"];
        std::cout << ", mapSizeX = " << text;
        text = levelMap["mapSizeY"];
        std::cout << ", mapSizeY = " << text << std::endl;
        std::cout << "GAME.CPP-LOADLEVEL: " << levelNumber << std::endl;
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
    if (eventManager.gameStop) isRunning = false;
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) return;
    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement () {
    if(player) {
    TransformComponent* mainPlayerTransform = player->GetComponent<TransformComponent>();

    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;

    }
}

void Game::CheckCollisions () {
    if(!manager.HasNoEntities()) manager.CollisionTrigger(eventManager);
}

void Game::Destroy() {
    eventManager.DestroyAllEvents();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}