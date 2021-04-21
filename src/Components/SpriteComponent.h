#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Animation.h"
#include <SDL2/SDL.h>
#include <iostream>

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
        std::map<std::string, Animation> animations;
        std::string currentAnimationName;
        unsigned int animationIndex = 0;

    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent(std::string id, bool isAnimated) {
            isAnimated = isAnimated;
            isFixed = false;
            SetTexture(id);
            #ifdef DEBUG
                std::cout << "...............ADDED-SPRITECOMPONENT: " << "id = " << id << std::endl;
            #endif
        }

        SpriteComponent(std::string id, unsigned int numFrames, unsigned int animationSpeed, bool hasDirections, bool isFixed) {
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

            #ifdef DEBUG
                std::cout << "...............ADDED-SPRITECOMPONENT: " << "id = " << id << ", numFrames = " << numFrames
                    << ", animationSpeed = " << animationSpeed << ", hasDirections = " << hasDirections
                    << ", isFixed = " << isFixed << std::endl;
            #endif
        }

        void Play(std::string animationName) {
            numFrames = animations[animationName].numFrames;
            animationIndex = animations[animationName].index;
            animationSpeed = animations[animationName].animationSpeed;
            currentAnimationName = animationName;
        }

        void SetTexture (std::string assetTextureId) {
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
            #ifdef DEBUG
                std::cout << "......UPDATE-SPRITE-" << this->owner->name << std::endl;
            #endif
            if (isAnimated) sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
            sourceRectangle.y = animationIndex * transform->height;
            destinationRectangle.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x);
            destinationRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
            destinationRectangle.w = transform->width * transform->scale;
            destinationRectangle.h = transform->height * transform->scale;
        }

        void Render() override {
            #ifdef DEBUG
                std::cout << "......RENDER-SPRITE-" << this->owner->name << std::endl; 
            #endif
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
        }
};

#endif