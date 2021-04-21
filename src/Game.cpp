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
    #ifdef DEBUG
        std::cout << "...GAME.CPP::INITIALIZE-BEGIN" << std::endl;
    #endif

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
    #ifdef DEBUG
        std::cout << "...GAME.CPP::INITIALIZE-END" << std::endl;
    #endif
    return;
}

void Game::LoadLevel(int levelNumber) {
    #ifdef DEBUG
        std::cout << "......GAME.CPP::LOADLEVEL" << levelNumber << "-BEGIN" << std::endl;
        std::cout << ".........SOL-CONF-BEGIN" << std::endl;
    #endif
    //Lua preparation
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

    std::string levelName = "Level" + std::to_string(levelNumber);
    lua.script_file("./assets/scripts/" + levelName + ".lua");

    sol::table levelData = lua[levelName];
    
    #ifdef DEBUG
        std::cout << ".........SOL-CONF-END" << std::endl;
        std::cout << ".........SOL-LOADING-ASSETS-BEGIN" << std::endl;
    #endif

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
                    std::cout << "............ADDED-ASSET: assetType = " << assetType << ", assetId = " << assetId << ", assetFile = " << assetFile << std::endl;
                #endif
            } else if (assetType.compare("font") == 0) {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                assetManager->AddFont(assetId, assetFile.c_str(), static_cast<int>(asset["fontSize"]));
            }
            assetsIndex++;
        }
    }

    #ifdef DEBUG
        std::cout << ".........SOL-LOADING-ASSETS-END" << std::endl;
        std::cout << ".........SOL-LOADING-MAP-BEGIN" << std::endl;
    #endif

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
        std::cout << "............ADDED-MAP: mapTextureId = " << mapTextureId << ", mapFile = " << mapFile;
        text = levelMap["scale"];
        std::cout << ", scale = " << text;
        text = levelMap["tileSize"];
        std::cout << ", tileSize = " << text;
        text = levelMap["mapSizeX"];
        std::cout << ", mapSizeX = " << text;
        text = levelMap["mapSizeY"];
        std::cout << ", mapSizeY = " << text << std::endl;
        std::cout << ".........SOL-LOADING-MAP-END" << std::endl;
        std::cout << ".........SOL-LOADING-ENTITIES-BEGIN" << std::endl;
    #endif

    /****************************************************/
    /* LOADING ENTITIES FORM LUA CONFIG FILE            */
    /****************************************************/

    sol::table entities = levelData["entities"];
    unsigned int entityIndex = 0;
    while (true) {
        sol::optional<sol::table> existsEntitiesIndexNode = entities[entityIndex];
        if (existsEntitiesIndexNode == sol::nullopt) {
            #ifdef DEBUG
                std::cout << ".........SOL-LOADING-ENTITIES-END" << std::endl;
            #endif
            break;
        } else {
            #ifdef DEBUG
                std::cout << "............LOADING-ENTITY-" << entityIndex << "-BEGIN" << std::endl;
            #endif
            //add new entity
            sol::table entity = entities[entityIndex];
            std::string entityName = entity["name"];
            auto& newEntity(manager.AddEntity(entityName, static_cast<LayerType>(static_cast<int>(entity["layer"]))));

            //add transform component
            sol::optional<sol::table> existsTransformIndexNode = entity["components"]["transform"];
            if (existsTransformIndexNode != sol::nullopt) {
                newEntity.AddComponent<TransformComponent>(
                    static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                    static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                    static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
                    static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
                    static_cast<int>(entity["components"]["transform"]["width"]),
                    static_cast<int>(entity["components"]["transform"]["height"]),
                    static_cast<int>(entity["components"]["transform"]["scale"])
                );
            }
            //add sprite component
            sol::optional<sol::table> existsSpriteIndexNode = entity["components"]["sprite"];
            if (existsSpriteIndexNode != sol::nullopt) {
                bool isAnimated = static_cast<bool>(entity["components"]["sprite"]["animated"]);
                if(isAnimated) {
                    std::string textureAssetId = entity["components"]["sprite"]["textureAssetId"];

                    newEntity.AddComponent<SpriteComponent>(
                        textureAssetId,
                        static_cast<int>(entity["components"]["sprite"]["frameCount"]),
                        static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
                        static_cast<bool>(entity["components"]["sprite"]["hasDirection"]),
                        static_cast<bool>(entity["components"]["sprite"]["fixed"])
                    );
                } else {
                    std::string textureAssetId = entity["components"]["sprite"]["textureAssetId"];

                    newEntity.AddComponent<SpriteComponent>(
                        textureAssetId,
                        isAnimated
                    );
                }
            }
            //add collider component
            sol::optional<sol::table> existsColliderIndexNode = entity["components"]["collider"];
            if (existsColliderIndexNode != sol::nullopt) {
                std::string colliderTag = entity["components"]["collider"]["tag"];
                newEntity.AddComponent<ColliderComponent>(
                    colliderTag,
                    static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                    static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                    static_cast<int>(entity["components"]["transform"]["width"]),
                    static_cast<int>(entity["components"]["transform"]["height"])
                );
            }
            //add keyboard control component
            sol::optional<sol::table> existsInputIndexNode = entity["components"]["input"];
            if (existsInputIndexNode != sol::nullopt) {
                std::string upKey = entity["components"]["input"]["keyboard"]["up"];
                std::string rightKey = entity["components"]["input"]["keyboard"]["right"];
                std::string downKey = entity["components"]["input"]["keyboard"]["down"];
                std::string leftKey = entity["components"]["input"]["keyboard"]["left"];
                std::string shootKey = entity["components"]["input"]["keyboard"]["shoot"];
                newEntity.AddComponent<KeyboardControlComponent>(upKey, rightKey, downKey, leftKey, shootKey);
            }
            //add projectile entity
            sol::optional<sol::table> existsProjectileEmitterIndexNode = entity["components"]["projectileEmitter"];
            if (existsProjectileEmitterIndexNode != sol::nullopt) {
                std::string entityProjectileName = entityName + "-projectile"; 
                auto& newProjectileEntity(manager.AddEntity(entityProjectileName, static_cast<LayerType>(4)));

                //add projectile transform component
                int offsetX = static_cast<int>(entity["components"]["transform"]["width"]) / 2 
                    - static_cast<int>(entity["components"]["projectileEmitter"]["width"]) /2; 
                int offsetY = static_cast<int>(entity["components"]["transform"]["height"]) / 2 
                    - static_cast<int>(entity["components"]["projectileEmitter"]["height"]) /2; 
                newProjectileEntity.AddComponent<TransformComponent>(
                    static_cast<int>(entity["components"]["transform"]["position"]["x"]) + offsetX,
                    static_cast<int>(entity["components"]["transform"]["position"]["y"]) + offsetY,
                    0,
                    0,
                    static_cast<int>(entity["components"]["projectileEmitter"]["width"]),
                    static_cast<int>(entity["components"]["projectileEmitter"]["height"]),
                    static_cast<int>(entity["components"]["transform"]["scale"])
                );
                //add projectile sprite
                std::string projectileTextureAssetId = entity["components"]["projectileEmitter"]["textureAssetId"];
                newProjectileEntity.AddComponent<SpriteComponent>(projectileTextureAssetId, false);

                //add projectile collider component
                std::string colliderTag = entity["components"]["collider"]["tag"];
                colliderTag = colliderTag + "-projectile";
                newProjectileEntity.AddComponent<ColliderComponent>(
                    colliderTag,
                    static_cast<int>(entity["components"]["transform"]["position"]["x"]) + offsetX,
                    static_cast<int>(entity["components"]["transform"]["position"]["y"]) + offsetY,
                    static_cast<int>(entity["components"]["projectileEmitter"]["width"]),
                    static_cast<int>(entity["components"]["projectileEmitter"]["height"])
                );

                //add projectile emitter component
                newProjectileEntity.AddComponent<ProjectileEmitterComponent>(
                    static_cast<int>(entity["components"]["projectileEmitter"]["speed"]),
                    static_cast<int>(entity["components"]["projectileEmitter"]["angle"]),
                    static_cast<int>(entity["components"]["projectileEmitter"]["range"]),
                    static_cast<bool>(entity["components"]["projectileEmitter"]["loop"])
                );
            }

            #ifdef DEBUG
                std::cout << "............LOADING-ENTITY-" << entityIndex << "-END" << std::endl;
            #endif
        }
        ++entityIndex;
        #ifdef DEBUG
            std::cout << ".........entityIndex = " << entityIndex << std::endl;
        #endif
    }

    #ifdef DEBUG
        std::cout << "GAME.CPP-LOADLEVEL" << levelNumber << "-END" << std::endl;
    #endif

    //get player entity (if exist)
    player = manager.GetEntitiesByName("player");
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

    //camera
    HandleCameraMovement();

    //events
    CheckCollisions();
    eventManager.HandleEvents();
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