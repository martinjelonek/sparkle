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
#include "./Components/RectangleComponent.h"
#include "./Components/MapEditorComponent.h"
#include "../lib/glm/glm.hpp"
#include <iostream>

using namespace glm;

EntityManager manager;
EventManager eventManager;
AssetManager *Game::assetManager = new AssetManager(&manager);
SDL_Renderer *Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Entity *player = NULL;
Map *map;

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

    LoadScene(0);

    isRunning = true;
    #ifdef DEBUG
        std::cout << "...GAME.CPP::INITIALIZE-END" << std::endl;
    #endif
    return;
}

void Game::LoadScene(int sceneNumber) {
    #ifdef DEBUG
        std::cout << "......GAME.CPP::LOADSCENE" << sceneNumber << "-BEGIN" << std::endl;
        std::cout << ".........SOL-PREPARATION-BEGIN" << std::endl;
    #endif
    //Camera reset
    Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    //Lua preparation
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

    std::string sceneName = "Scene" + std::to_string(sceneNumber);
    lua.script_file("./assets/scripts/" + sceneName + ".lua");

    sol::table levelData = lua[sceneName];
    
    #ifdef DEBUG
        std::cout << ".........SOL-PREPARATION-END" << std::endl;
        std::cout << ".........SOL-LOADING-CONF-BEGIN" << std::endl;
    #endif
    
    /****************************************************/
    /* LOADING CONF FORM LUA CONFIG FILE                */
    /****************************************************/
    sol::table levelConf = levelData["conf"];
    sceneSize.x = static_cast<int>(levelConf["sceneWidth"]);
    sceneSize.y = static_cast<int>(levelConf["sceneHeight"]);

    #ifdef DEBUG
        std::cout << ".........SOL-LOADING-CONF-END" << std::endl;
        std::cout << ".........SOL-LOADING-CONTROL-BEGIN" << std::endl;
    #endif
    
    /****************************************************/
    /* LOADING CONTROL FROM LUA CONFIG FILE             */
    /****************************************************/
    sol::table levelControl = levelData["control"];
    key1 = levelControl["keyboard"]["key1"];
    key2 = levelControl["keyboard"]["key2"];
    keyEsc = levelControl["keyboard"]["keyEsc"];
    keyEnter = levelControl["keyboard"]["keyEnter"];

    #ifdef DEBUG
        std::cout << ".........SOL-LOADING-CONTROL-END" << std::endl;
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
                #ifdef DEBUG
                    std::cout << "............ADDED-ASSET: assetType = " << assetType << ", assetId = " << assetId << ", assetFile = " << assetFile << std::endl;
                #endif
            }
            assetsIndex++;
        }
    }

    #ifdef DEBUG
        std::cout << ".........SOL-LOADING-ASSETS-END" << std::endl;
        std::cout << ".........SOL-LOADING-MAP-BEGIN" << std::endl;
    #endif

    /****************************************************/
    /* LOADING MAPS FORM LUA FILE                       */
    /****************************************************/
    sol::optional<sol::table> existsMapNode = levelData["map"];
    if(existsMapNode == sol::nullopt) {
        #ifdef DEBUG
            std::cout << ".........SOL-MAPNOTDETECTED" << std::endl;
        #endif
    } else {
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
    }    

    /****************************************************/
    /* LOADING ENTITIES FORM LUA FILE                   */
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
                    static_cast<float>(entity["components"]["transform"]["scale"])
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
                        isAnimated,
                        static_cast<bool>(entity["components"]["sprite"]["fixed"])
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
                newEntity.AddComponent<KeyboardControlComponent>(upKey, rightKey, downKey, leftKey, shootKey, sceneSize.x, sceneSize.y);
            }
            //add label component
            sol::optional<sol::table> existsLabelIndexNode = entity["components"]["label"];
            if (existsLabelIndexNode != sol::nullopt) {
                std::string text = entity["components"]["label"]["text"];
                std::string fontFamily = entity["components"]["label"]["fontFamily"];
                std::string color = entity["components"]["label"]["color"];
                newEntity.AddComponent<TextLabelComponent>(
                    static_cast<int>(entity["components"]["label"]["x"]),
                    static_cast<int>(entity["components"]["label"]["y"]),
                    text,
                    fontFamily,
                    color
                );
            }

            //add rectangle component
            sol::optional<sol::table> existsRectangleIndexNode = entity["components"]["rectangle"];
            if (existsRectangleIndexNode != sol::nullopt) {
                newEntity.AddComponent<RectangleComponent>(
                    static_cast<int>(entity["components"]["rectangle"]["x"]),
                    static_cast<int>(entity["components"]["rectangle"]["y"]),
                    static_cast<int>(entity["components"]["rectangle"]["w"]),
                    static_cast<int>(entity["components"]["rectangle"]["h"]),
                    static_cast<int>(entity["components"]["rectangle"]["r"]),
                    static_cast<int>(entity["components"]["rectangle"]["g"]),
                    static_cast<int>(entity["components"]["rectangle"]["b"])
                );
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
                    static_cast<bool>(entity["components"]["projectileEmitter"]["loop"]),
                    newEntity.GetComponent<TransformComponent>()
                );
            }
            //add map editor component set
            sol::optional<sol::table> existsMapEditorIndexNode = entity["components"]["mapeditor"];
            if (existsMapEditorIndexNode != sol::nullopt) {
                std::string labelNameX = entity["components"]["mapeditor"]["labelNameX"];
                std::string labelNameY = entity["components"]["mapeditor"]["labelNameY"];
                std::string fontFamily = entity["components"]["mapeditor"]["fontFamily"];
                std::string mapTextureId = entity["components"]["mapeditor"]["mapTextureId"];
                std::string mapToLoadName = entity["components"]["mapeditor"]["mapToLoadName"];
                newEntity.AddComponent<MapEditorComponent>(
                    &manager,
                    labelNameX,
                    labelNameY,
                    static_cast<int>(entity["components"]["mapeditor"]["mapSizeX"]),
                    static_cast<int>(entity["components"]["mapeditor"]["mapSizeY"]),
                    fontFamily,
                    mapTextureId,
                    static_cast<int>(entity["components"]["mapeditor"]["mapScale"]),
                    static_cast<int>(entity["components"]["mapeditor"]["mapTileSize"]),
                    static_cast<int>(entity["components"]["mapeditor"]["mapDefaultPositionX"]),
                    static_cast<int>(entity["components"]["mapeditor"]["mapDefaultPositionY"]),
                    mapToLoadName,
                    static_cast<int>(entity["components"]["mapeditor"]["mapToLoadSizeX"]),
                    static_cast<int>(entity["components"]["mapeditor"]["mapToLoadSizeY"])
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
        std::cout << "GAME.CPP-LOADSCENE" << sceneNumber << "-END" << std::endl;
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
        //KEY - 1
        if(event.key.keysym.sym == SDLK_1) {
        
            #ifdef DEBUG
                std::cout << "......KEY 1 PRESSED: value " << key1 << std::endl;
            #endif
            if (key1.compare("NULL") != 0) {
                if(SDL_GetTicks() - sceneChangeCooldown > 500) {
                    manager.ClearData();
                    eventManager.DestroyAllEvents();
                    LoadScene(std::stoi(key1));
                    sceneChangeCooldown = SDL_GetTicks();
                }
            }
        }
        //KEY - 2
        if(event.key.keysym.sym == SDLK_2) {
        
            #ifdef DEBUG
                std::cout << "......KEY 2 PRESSED: value " << key1 << std::endl;
            #endif
            if (key2.compare("NULL") != 0) {
                if(SDL_GetTicks() - sceneChangeCooldown > 500) {
                    manager.ClearData();
                    eventManager.DestroyAllEvents();
                    LoadScene(std::stoi(key2));
                    sceneChangeCooldown = SDL_GetTicks();
                }                    
            }
        }
        //KEY - ESC
        if(event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN) {
            #ifdef DEBUG
                std::cout << "......KEY ENTER PRESSED: value " << key1 << std::endl;
            #endif
            if (keyEnter.compare("NULL") != 0) {
                if(SDL_GetTicks() - sceneChangeCooldown > 500) {
                    manager.ClearData();
                    eventManager.DestroyAllEvents();
                    LoadScene(std::stoi(keyEnter));
                    sceneChangeCooldown = SDL_GetTicks();
                }                
            }
        }
        //KEY - ENTER
        if(event.key.keysym.sym == SDLK_ESCAPE) {
            #ifdef DEBUG
                std::cout << "......KEY ESC PRESSED: value " << keyEsc << std::endl;
            #endif
            if (keyEsc.compare("NULL") == 0) {

            } else if (keyEsc.compare("CLOSE") == 0) {
                if(SDL_GetTicks() - sceneChangeCooldown > 500) {
                    isRunning = false;
                }
            } else {
                if(SDL_GetTicks() - sceneChangeCooldown > 500) {
                    manager.ClearData();
                    eventManager.DestroyAllEvents();
                    LoadScene(std::stoi(keyEsc));
                    sceneChangeCooldown = SDL_GetTicks();
                }
            }       
        }
    default:
        break;
    }
    manager.ProcessInput(event);
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
    camera.x = camera.x > (sceneSize.x - camera.w) ? (sceneSize.x - camera.w) : camera.x;
    camera.y = camera.y > (sceneSize.y - camera.h) ? (sceneSize.y - camera.h) : camera.y;
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