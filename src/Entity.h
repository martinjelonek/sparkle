#ifndef ENTITY_H
#define ENTITY_H

#include "./Component.h"
#include "./EntityManager.h"
#include <vector>
#include <string>

using namespace std;

class Component;
class EntityManager;

class Entity {
    private:
        bool isActive;
        EntityManager& manager;
        vector<Component*> components;
    public:
        string name;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;
};

#endif