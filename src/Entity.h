#ifndef ENTITY_H
#define ENTITY_H

#include "./Component.h"
#include "./EntityManager.h"
#include "./Constants.h"
#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include <string>

class Component;
class EntityManager;

class Entity {
    private:
        bool isActive;
        EntityManager& manager;
        std::vector<Component*> components;
        std::map<const std::type_info*, Component*> componentTypeMap;
    public:
        std::string name;
        LayerType layer;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name, LayerType layer);
        void ProcessInput(SDL_Event& event);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;
        void ListAllComponents() const;

        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args) {
            T* newComponent(new T(std::forward<TArgs>(args)...));
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

        template<typename T>
        bool HasComponent() const {
            return componentTypeMap.count(&typeid(T));
        }
};

#endif