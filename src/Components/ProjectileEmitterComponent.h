#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include "../Constants.h"
#include "../../lib/glm/glm.hpp"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"

class ProjectileEmitterComponent: public Component {
    private:
        TransformComponent *transform;
        TransformComponent *parentTransform;
        glm::vec2 origin;
        int speed;
        int range;
        float angleRad;
        bool loop;
    public:
        ProjectileEmitterComponent(int speed, int angleDeg, int range, bool loop, TransformComponent *parentTransform) {
            this->speed = speed;
            this->range = range;
            this->loop = loop;
            this->angleRad = glm::radians(static_cast<float>(angleDeg));
            this->parentTransform = parentTransform;
            #ifdef DEBUG
                #include <string>
                std::cout << "...............ADDED-PROJECTILEEMITTERCOMPONENT: " 
                << "speed = " << speed 
                << ", angleDeg = " << angleDeg 
                << ", range = " << range 
                << ", loop = " << loop
                << ", parentTransform = " << parentTransform
                << std::endl;
            #endif
        }

        void Initialize() override {
            transform = owner->GetComponent<TransformComponent>();
            origin = glm::vec2(parentTransform->position.x, parentTransform->position.y);
            transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
        }

        void Update(float deltaTime) override {
            #ifdef DEBUG
                if (SHOW_COMPONENTS_UPDATE) {
                    std::cout << "......UPDATE-PROJECTILEEMITTER-" << this->owner->name << std::endl;
                }
            #endif
            if (glm::distance(transform->position, origin) > range) {
                if(loop) {
                    origin.x = parentTransform->position.x;
                    origin.y = parentTransform->position.y;
                    transform->position.x = origin.x;
                    transform->position.y = origin.y;
                }else{
                    owner->Destroy();
                }
            }
        }
};

#endif