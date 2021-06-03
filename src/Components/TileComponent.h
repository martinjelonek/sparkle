#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>

using namespace glm;

class TileComponent: public Component {
    public:
    SDL_Texture *texture;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    vec2 position;
    bool visibility;

    TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId, bool visibility) {
        texture = Game::assetManager->GetTexture(assetTextureId);

        sourceRectangle.x = sourceRectX;
        sourceRectangle.y = sourceRectY;
        sourceRectangle.w = tileSize;
        sourceRectangle.h = tileSize;

        destinationRectangle.x = x;
        destinationRectangle.y = y;
        destinationRectangle.w = tileSize * tileScale;
        destinationRectangle.h = destinationRectangle.w;

        position.x = x;
        position.y = y;

        this->visibility = visibility;
    }

    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }

    void Update (float deltaTime) override {
        destinationRectangle.x = position.x - Game::camera.x;
        destinationRectangle.y = position.y - Game::camera.y;
    }

    void Render () override {
        if (visibility) {
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
        }
    }

    void SetSourceRectanglePosition (int x, int y) {
        this->sourceRectangle.x = x;
        this->sourceRectangle.y = y;
    }

    void SetVisibility (bool visibility) {
        this->visibility = visibility;
    }
};

#endif