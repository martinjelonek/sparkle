#include "./EntityManager.h"
#include "./Collision.h"
#include "./Components/ColliderComponent.h"
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
    DestroyInactiveEntities();
}

void EntityManager::DestroyInactiveEntities() {
    for (int i = 0; i < entities.size(); i++) {
        if (!entities[i]->IsActive()) entities.erase(entities.begin() + i);
    }
}

void EntityManager::Render() {
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
        for (auto& entity: GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) {
            entity->Render();
        }
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

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
    std::vector<Entity*> selectedEntites;
    for (auto& entity: entities) {
        if(entity->layer == layer) {
            selectedEntites.emplace_back(entity);
        }
    }
    return selectedEntites;
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

void EntityManager::CollisionTrigger (EventManager& EventManager) {
    for (int i = 0; i < entities.size() - 1; i++) {
        auto& EntityA = entities[i];
        if (EntityA->HasComponent<ColliderComponent>()) {
            ColliderComponent* ColliderA = EntityA->GetComponent<ColliderComponent>();
            for (int j = i + 1; j < entities.size(); j++) {
                auto& EntityB = entities[j];
                if (EntityA->name.compare(EntityB->name) != 0 && EntityB->HasComponent<ColliderComponent>()) {
                    ColliderComponent* ColliderB = EntityB->GetComponent<ColliderComponent>();
                    if (Collision::CheckRectangleCollision(ColliderA->collider, ColliderB->collider)) {
                        
                    }
                }
            }
        }
    }
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