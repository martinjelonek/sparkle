#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "./Entity.h"
#include "./Component.h"
#include <string>
#include <vector>

class EntityManager {
    private:
        std::vector<Entity*> entities;
    public:
        void ClearData();
        void Update(float deltaTime);
        void Render();
        bool HasNoEntities() const;
        unsigned int GetEntityCount() const;
        void ListAllEntities() const;       
        std::vector<Entity*> GetEntities() const;
        Entity& AddEntity(std::string entityName);       
};

#endif