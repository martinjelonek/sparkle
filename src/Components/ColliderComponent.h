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
            #ifdef DEBUG
                std::cout << "...............ADDED-COLLIDERCOMPONENT: " << "colliderTag = " << colliderTag << std::endl;
            #endif
        }

        void Initialize() override {
            if (owner->HasComponent<TransformComponent>()) {
                transform = owner->GetComponent<TransformComponent>();  
                sourceRectangle = {0, 0, transform->width, transform->height};
                destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
            }
        }

        void Update(float deltaTime) override {
            #ifdef DEBUG
                std::cout << "......UPDATE-COLLIDERCOMPONENT-" << this->owner->name << std::endl;
            #endif
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
            destinationRectangle.x = collider.x - Game::camera.x;
            destinationRectangle.y = collider.y - Game::camera.y;                
        }

        #ifdef DEBUG
            void Render() override {
                #include "../Constants.h"
                if (SHOW_COLLIDER_BOX) {    
                    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
                    SDL_RenderDrawRect(Game::renderer, &destinationRectangle);                    
                }
            }
        #endif
};

#endif