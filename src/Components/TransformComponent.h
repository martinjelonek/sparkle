#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../EntityManager.h"
#include "../Game.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>
#include <iostream>

using namespace glm;

class TransformComponent: public Component {
    public:
        vec2 position;
        vec2 velocity;
        int width;
        int height;
        float scale;

        TransformComponent(int posX, int posY, int velX, int velY, int w, int h, float s) {
            position = vec2(posX, posY);
            velocity = vec2(velX, velY);
            width = w;
            height = h;
            scale = s;
            #ifdef DEBUG
                std::cout << "...............ADDED-TRANSFORMCOMPONENT: " 
                << "posX = " << posX 
                << ", posY = " << posY 
                << ", velX = " << velX 
                << ", velY = " << velY 
                << ", w = " << w 
                << ", h = " << h 
                << ", scale = " << s << std::endl;
            #endif
        }

        void Initialize() override{

        }

        void Update(float deltaTime) override {
            #ifdef DEBUG
                std::cout << "......UPDATE-TRANSFORMCOMPONENT-" << this->owner->name << std::endl;
            #endif
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
        }

         #ifdef DEBUG
            void Render() override {
                #include "../Constants.h"
                if (SHOW_TRANSFORM_BOX) {    
                    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
                    SDL_RenderDrawLine (
                        Game::renderer, 
                        position.x - Game::camera.x, 
                        position.y - Game::camera.y, 
                        position.x + velocity.x - Game::camera.x, 
                        position.y + velocity.y - Game::camera.y
                    );
                    SDL_Rect vecEnd = {
                        position.x + velocity.x - 5 - Game::camera.x, 
                        position.y + velocity.y + 5 - Game::camera.y,
                        10, 
                        -10
                    };
                    SDL_RenderDrawRect(Game::renderer, &vecEnd);
                }
            }
        #endif
};

#endif