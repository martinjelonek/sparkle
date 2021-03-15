#include "./EntityManager.h"

void EntityManager::ClearData() {
    for (auto& entity: entities) {
        entity->Destroy();
    }
}

bool EntityManager::HasNoEntities() {
    return entities.size() == 0;
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

Entity& EntityManager::AddEntity(string entityName) {
    Entity *entity = new Entity(*this, entityName);
    entities.emplace_back(entity);
    return *entity;
}

vector<Entity*> EntityManager::GetEntities() const {
    return entities;
}

unsigned int EntityManager::GetEntityCount() {
    return entities.size();
}