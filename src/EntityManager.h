#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "./Entity.h"
#include "./Component.h"
#include <string>
#include <vector>

using namespace std;

class EntityManager {
    private:
        vector<Entity*> entities;
    public:
        void ClearData();
        void Update(float deltaTime);
        void Render();
        bool HasNoEntities() const;
        unsigned int GetEntityCount() const;
        void ListAllEntities() const;       
        vector<Entity*> GetEntities() const;
        Entity& AddEntity(string entityName);       
};

#endif