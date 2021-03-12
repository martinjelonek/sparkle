#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>

using namespace std;

class EntityManager;
class Component;

class Entity{
    private:
        EntityManager& manager;
        bool isActive;
        vector<Component*> components;

    public:
        string name;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool isActive() const;
    
};

#endif