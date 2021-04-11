#include "./EntityManager.h"
#include <iostream>

void EntityManager::ClearData() {
    for (auto& entity: entities) {
        entity->Destroy();
    }
}

void EntityManager::Update(float deltaTime) {
    for (auto& entitiy: entities) {
        entitiy->Update(deltaTime);
    }
}

void EntityManager::Render() {
    for (auto& entity: entities) {
        entity->Render();
    }
}

bool EntityManager::HasNoEntities() const {
    return entities.size() == 0;
}

unsigned int EntityManager::GetEntityCount() const {
    return entities.size();
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return entities;
}

Entity& EntityManager::AddEntity(std::string entityName) {
    Entity *entity = new Entity(*this, entityName);
    entities.emplace_back(entity);
    return *entity;
}

#ifdef DEBUG
    void EntityManager::ListAllEntities() const {
        unsigned int i = 0;
        for (auto& entity: entities) {
            std::cout << "...Entity " << i << " : <" << entity->name << ">" << std::endl;
            entity->ListAllComponents();
            i++;
        }
    }
#endif