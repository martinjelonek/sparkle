#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include "../../lib/glm/glm.hpp"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"

class ProjectileEmitterComponent: public Component {
    private:
        TransformComponent *transform;
        glm::vec2 origin;
        int speed;
        int range;
        float angleRad;
        bool loop;
    public:
        ProjectileEmitterComponent(int speed, int angleDeg, int range, bool loop) {
            this->speed = speed;
            this->range = range;
            this->loop = loop;
            this->angleRad = glm::radians(static_cast<float>(angleDeg));
        }

        void Initialize() override {
            transform = owner->GetComponent<TransformComponent>();
            origin = glm::vec2(transform->position.x, transform->position.y);
            transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
        }

        void Update(float deltaTime) override {
            if (glm::distance(transform->position, origin) > range) {
                if(loop) {
                    transform->position.x = origin.x;
                    transform->position.y = origin.y;
                }else{
                    owner->Destroy();
                }
            }
        }
};

#endif