#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

class Entity;

class Component {
    public:
        Entity* owner;
        virtual ~Component() {}
        virtual void Initialize() {}
        virtual void ProcessInput(SDL_Event& event) {}
        virtual void Update(float deltaTime) {}
        virtual void Render() {}
};

#endif