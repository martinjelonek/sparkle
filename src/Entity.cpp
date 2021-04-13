#include "./Entity.h"
#include <iostream>

Entity::Entity(EntityManager& manager): manager(manager) {
    this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer): manager(manager), name(name), layer(layer) {
    this->isActive = true;
}

void Entity::Update(float deltaTime) {
    //loop vector of components
    for (auto& component: components) {
        component->Update(deltaTime);
    }
}

void Entity::Render() {
    //loop vector of components
    for (auto& component: components){
        component->Render();
    }
}

void Entity::Destroy() {
    this->isActive = false;
}

bool Entity::IsActive() const {
    return this->isActive;
}

#ifdef DEBUG
    void Entity::ListAllComponents() const {
        for(auto mapElement: componentTypeMap) {
            std::cout << "......ENTITY_CPP-LISTALLCOMPONENTS: <" << mapElement.first->name() << ">" << std::endl;
        }
    }
#endif