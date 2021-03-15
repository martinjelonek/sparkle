#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../EntityManager.h"
#include "../Game.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>

using namespace glm;

class TransformComponent: public Component {
    public:
        vec2 position;
        vec2 velocity;
        int width;
        int height;
        int scale;

        TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
            position = vec2(posX, posY);
            velocity = vec2(velX, velY);
            width = w;
            height = h;
            scale = s;
        }

        void Initialize() override{

        }

        void Update(float deltaTime) override {
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
        } 

        void Render() override {
            SDL_Rect transformRectangle = {
                (int) position.x,
                (int) position.y,
                width,
                height
            };
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(Game::renderer, &transformRectangle);
        }
};

#endif