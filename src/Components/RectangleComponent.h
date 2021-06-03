#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H

#include "SDL2/SDL.h"
#include "../Game.h"
#include "../EntityManager.h"

class RectangleComponent: public Component {
    public:
        SDL_Rect rect;
        int r;
        int g;
        int b;

        RectangleComponent(int x, int y, int w, int h, int r, int g, int b) {
            this->rect.x = x;
            this->rect.y = y;
            this->rect.w = w;
            this->rect.h = h;
            this->r = r;
            this->g = g;
            this->b = b;

            #ifdef DEBUG
                std::cout << "...............ADDED-RECTANGLECOMPOENENT: " 
                << "x = " << x << ", y = " << y << ", w = " << w << ", h = " << h
                << ",R = " << r << ", G = " << g << ", B = " << b << std::endl;
            #endif
        }

        void Render() override {
            SDL_SetRenderDrawColor(Game::renderer, r, g, b, 255);
            SDL_RenderFillRect(Game::renderer, &rect);
        }
};

#endif