#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Animation.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class SpriteComponent: public Component {
    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        bool isAnimated;
        int numFrames;
        int animationSpeed;
        bool isFixed;
        map<string, Animation> animations;
        string currentAnimationName;
        unsigned int animationIndex = 0;

    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent(const char* filePath) {
            isAnimated = false;
            isFixed = false;
            SetTexture(filePath);
        }

        SpriteComponent(string id, unsigned int numFrames, unsigned int animationSpeed, bool hasDirections, bool isFixed) {
            this->isAnimated = true;
            this->numFrames = numFrames;
            this->animationSpeed = animationSpeed;
            this->isFixed = isFixed;

            if(hasDirections) {
                Animation upAnimation = Animation(0, numFrames, animationSpeed);
                Animation downAnimation = Animation(1, numFrames, animationSpeed);
                Animation rightAnimation = Animation(2, numFrames, animationSpeed);
                Animation leftAnimation = Animation(3, numFrames, animationSpeed);
                animations.emplace("UpAnimation", upAnimation);
                animations.emplace("DownAnimation", downAnimation);
                animations.emplace("RightAnimation", rightAnimation);
                animations.emplace("LeftAnimation", leftAnimation);
                this->animationIndex = 0;
                this->currentAnimationName = "UpAnimation";
            } else {
                Animation singleAnimation = Animation(0, numFrames, animationSpeed);
                animations.emplace("SingleAnimation", singleAnimation);
                this->animationIndex = 0;
                this->currentAnimationName = "SingleAnimation";
            }
            
            Play(this->currentAnimationName);

            SetTexture(id);
        }

        void Play(string animationName) {
            numFrames = animations[animationName].numFrames;
            animationIndex = animations[animationName].index;
            animationSpeed = animations[animationName].animationSpeed;
            currentAnimationName = animationName;
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
            if (isAnimated) sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
            sourceRectangle.y = animationIndex * transform->height;
            destinationRectangle.x = static_cast<int>(transform->position.x);
            destinationRectangle.y = static_cast<int>(transform->position.y);
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