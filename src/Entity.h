#ifndef ENTITY_H
#define ENTITY_H

#include "./Component.h"
#include "./EntityManager.h"
#include <map>
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
        map<const type_info*, Component*> componentTypeMap;
    public:
        string name;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;

        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args) {
            T* newComponent(new T(forward<TArgs>(args)...));

            newComponent->owner = this;
            components.emplace_back(newComponent);
            componentTypeMap[&typeid(*newComponent)] = newComponent;
            newComponent->Initialize();
            return *newComponent;
        }

        template <typename T>
        T* GetComponent() {
            return static_cast<T*>(componentTypeMap[&typeid(T)]);
        }
};

#endif