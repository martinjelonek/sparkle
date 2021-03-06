#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "./Entity.h"
#include "./Game.h"
#include "./Component.h"
#include "./Constants.h"
#include "./EventManager.h"
#include <string>
#include <vector>

class EntityManager {
    private:
        std::vector<Entity*> entities;
        void DestroyInactiveEntities();
    public:
        void ClearData();
        void ProcessInput(SDL_Event& event);
        void Update(float deltaTime);
        void Render();
        bool HasNoEntities() const;
        unsigned int GetEntityCount() const;
        void ListAllEntities() const;       
        std::vector<Entity*> GetEntities() const;
        std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
        Entity* GetEntitiesByName(std::string entityName) const;
        Entity& AddEntity(std::string entityName, LayerType layer);
        void CollisionTrigger(EventManager& eventManager, int sceneToLoad);
};

#endif