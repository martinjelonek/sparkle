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

using namespace glm;

class AssetManager;

class Game {
    private:      
        SDL_Window *window;
        vec2 sceneSize;
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
        void LoadLevel(int levelNumber);
        void Initialize(int width, int height);
        void ProcessInput ();
        void Update();
        void Render();
        void HandleCameraMovement();
        void CheckCollisions();
        void Destroy();
};

#endif