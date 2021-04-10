#ifndef KEYBOARDCONTROLCOMPONENT_H
#define KEYBOARDCONTROLCOMPONENT_H

#include "../Constants.h"
#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

using namespace std;

class KeyboardControlComponent: public Component {
    public:
        string upKey;
        string downKey;
        string rightKey;
        string leftKey;
        string shootKey;
        TransformComponent *transform;
        SpriteComponent *sprite;

        KeyboardControlComponent () {

        }

        KeyboardControlComponent (string upKey, string rightKey, string downKey, string leftKey, string shootKey) {
            this->upKey = GetSDLKeyStringCode(upKey);
            this->rightKey = GetSDLKeyStringCode(rightKey);
            this->downKey = GetSDLKeyStringCode(downKey);
            this->leftKey = GetSDLKeyStringCode(leftKey);
            this->shootKey = GetSDLKeyStringCode(shootKey);
        }

        string GetSDLKeyStringCode(string key) {
            if (key.compare("up") == 0) return "1073741906";
            if (key.compare("right") == 0) return "1073741903";
            if (key.compare("down") == 0) return "1073741905";
            if (key.compare("left") == 0) return "1073741904";
            if (key.compare("space") == 0) return "32";
            return to_string(static_cast<int>(key[0]));
        }

        void Initialize () override {
            transform = owner->GetComponent<TransformComponent>();
            sprite = owner->GetComponent<SpriteComponent>();
        }

        void Update (float deltaTime) override {
            if(Game::event.type == SDL_KEYDOWN) {
                string keyCode = to_string(Game::event.key.keysym.sym);

                if(keyCode.compare(upKey) == 0) {
                    if (transform->position.y <= 0) {
                        transform->velocity.y = 0;
                        transform->velocity.x = 0;
                    } else {
                        transform->velocity.y = -25;
                        transform->velocity.x = 0;
                    }
                    sprite->Play("UpAnimation");
                }
                if(keyCode.compare(rightKey) == 0) {
                    if (transform->position.x + transform->width >= WINDOW_WIDTH) {
                        transform->velocity.y = 0;
                        transform->velocity.x = 0;
                    } else {
                        transform->velocity.y = 0;
                        transform->velocity.x = 25;
                    }
                    sprite->Play("RightAnimation");
                }
                if(keyCode.compare(downKey) == 0) {
                    if (transform->position.y + transform->height >= WINDOW_HEIGHT) {
                        transform->velocity.y = 0;
                        transform->velocity.x = 0;
                    } else {
                        transform->velocity.y = 25;
                        transform->velocity.x = 0;
                    }
                    sprite->Play("DownAnimation");
                }
                if(keyCode.compare(leftKey) == 0) {
                    if (transform->position.x <= 0) {
                        transform->velocity.y = 0;
                        transform->velocity.x = 0;
                    } else {
                        transform->velocity.y = 0;
                        transform->velocity.x = -25;
                    }
                    sprite->Play("LeftAnimation");
                }
                if(keyCode.compare(shootKey) == 0) {
                    //TODO:
                    //Shoot projectile when "shoot" key is pressed
                }
            }

            if(Game::event.type == SDL_KEYUP) {
                string keyCode = to_string(Game::event.key.keysym.sym);

                if(keyCode.compare(upKey) == 0) {
                    transform->velocity.y = 0;
                }
                if(keyCode.compare(rightKey) == 0) {
                    transform->velocity.x = 0;
                }
                if(keyCode.compare(downKey) == 0) {
                    transform->velocity.y = 0;
                }
                if(keyCode.compare(leftKey) == 0) {
                    transform->velocity.x = 0;
                }
            }      
        }
};

#endif