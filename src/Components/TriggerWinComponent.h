#ifndef TRIGGERCOMPONENT_H
#define TRIGGERCOMPONENT_H

#include "../EntityManager.h"
#include "../EventManager.h"
#include "../Constants.h"
#include "./TransformComponent.h"
#include <iostream>

class TriggerWinComponent: public Component {
    private:
        EventManager *eventManager;
        TransformComponent *transform;
        int sceneWidth;
        int sceneToLoad;
    public:
        TriggerWinComponent (EventManager *eventManager, int sceneWidth, int sceneToLoad) {
            this->eventManager = eventManager;
            this->sceneWidth = sceneWidth;
            this->sceneToLoad = sceneToLoad;
        }

        void Initialize () override {
            transform = owner->GetComponent<TransformComponent>();
        }

        void Update(float deltaTime) override {
            #ifdef DEBUG
                std::cout << "......UPDATE-TRIGGERWINCOMPONENT-" << this->owner->name << std::endl;
            #endif
            if(transform->position.x + transform->width >= sceneWidth) eventManager->AddWinEvent(WIN, sceneToLoad);
        }

        ~TriggerWinComponent () {}
};

#endif