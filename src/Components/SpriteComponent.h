#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../AssetManager.h"
#include "./TransformComponent.h"
#include "../TextureManager.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class SpriteComponent: public Component {
    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent(const char* filePath) {
            SetTexture(filePath);
        }

        void SetTexture (string assetTextureId) {
            texture = Game::assetManager->GetTexture(assetTextureId);
        }

        void Initialize() override {
            transform = owner->GetComponent<TransformComponent>();
            sourceRectangle.x = 0;
            sourceRectangle.y = 0;
            sourceRectangle.w = transform->width;
            sourceRectangle.h = transform->height;
        }

        void Update(float deltaTime) {
            destinationRectangle.x = (int) transform->position.x;
            destinationRectangle.y = (int) transform->position.y;
            destinationRectangle.w = transform->width * transform->scale;
            destinationRectangle.h = transform->height * transform->scale;
            #ifdef DEBUG
                cout << "...SPRITECOMPONENT_H-UPDATE: " << this->owner << endl;
            #endif
        }

        void Render() override {
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
            #ifdef DEBUG
                cout << "...SPRITECOMPONENT_H-RENDER: " << this->owner << endl; 
            #endif
        }
};

#endif