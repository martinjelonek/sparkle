#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"

class ColliderComponent: public Component {
    public:
        std::string colliderTag;
        SDL_Rect collider;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        TransformComponent* transform;

        ColliderComponent(std::string colliderTag, int x, int y, int width, int height) {
            this->colliderTag = colliderTag;
            this->collider = {x, y, width, height};
        }

        void Initialize() override {
            if (owner->HasComponent<TransformComponent>()) {
                transform = owner->GetComponent<TransformComponent>();  
                sourceRectangle = {0, 0, transform->width, transform->height};
                destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
            }
        }

        void Update(float deltaTime) override {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
            destinationRectangle.x = collider.x - Game::camera.x;
            destinationRectangle.y = collider.y - Game::camera.y;
        }

        void CollisionTriger (std::string& otherColliderTag, bool& gameIsRunning) {
            if (colliderTag.compare("player"))
            {
                if (otherColliderTag.compare("enemy")) CollisonWithEnemy(gameIsRunning);
            }
        }

        #ifdef DEBUG
            void Render() override {
                #include "../Constants.h"
                if (SHOW_COLLIDER_BOX) {    
                    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
                    SDL_RenderDrawRect(Game::renderer, &collider);                    
                }
            }
        #endif

        private:

        void CollisonWithEnemy(bool& gameIsRunning) {
                #ifdef DEBUG
                    #include <iostream>
                    std::cout << "......COLIDER_COMPONENT_H-PLAYER_COLLISON_TRIGER" << std::endl;
                #endif
                gameIsRunning = false;
        }
};

#endif