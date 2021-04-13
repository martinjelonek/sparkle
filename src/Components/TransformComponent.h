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
        int scale;

        TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
            position = vec2(posX, posY);
            velocity = vec2(velX, velY);
            width = w;
            height = h;
            scale = s;
            #ifdef DEBUG
                std::cout << "......TRANSFORMCOMPONENT_H:" << posX << "-"<< posY << "-"<< velX << "-" << velY << "-" << w << "-" << h << "-" << s << std::endl;
            #endif
        }

        void Initialize() override{

        }

        void Update(float deltaTime) override {
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
        }
};

#endif