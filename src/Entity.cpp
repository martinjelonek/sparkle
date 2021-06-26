#include "./Entity.h"
#include "./Constants.h"
#include <iostream>

Entity::Entity(EntityManager& manager): manager(manager) {
    this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer): manager(manager), name(name), layer(layer) {
    this->isActive = true;
}

void Entity::ProcessInput(SDL_Event& event) {
    for (auto& component: components) {
        component->ProcessInput(event);
    }
}

void Entity::Update(float deltaTime) {
    for (auto& component: components) {
        component->Update(deltaTime);
    }
}

void Entity::Render() {
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