#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/glm/glm.hpp"
#include "../lib/lua/sol.hpp"
#include "./Entity.h"
#include "./Component.h"
#include "./EntityManager.h"
#include <string>

using namespace glm;

class AssetManager;

class Game {
    private:      
        SDL_Window *window;
        vec2 sceneSize;
        std::string key1 = "NULL";
        std::string key2 = "NULL";
        std::string keyEsc = "QUIT";
        std::string keyEnter = "NULL";
        unsigned int sceneChangeCooldown = 0;

    public:
        Game();
        ~Game();
        bool isRunning;  
        int ticksLastFrame = 0;
        bool IsRunning() const;        
        static SDL_Renderer *renderer;
        static AssetManager* assetManager;
        static SDL_Event event;
        static SDL_Rect camera;
        void LoadScene(int levelNumber);
        void Initialize(int width, int height);
        void ProcessInput ();
        void Update();
        void Render();
        void HandleCameraMovement();
        void CheckCollisions();
        void Destroy();
};

#endif