#include "./Entity.h"
#include <iostream>

using namespace std;

Entity::Entity(EntityManager& manager): manager(manager) {
    this->isActive = true;
}

Entity::Entity(EntityManager& manager, string name): manager(manager), name(name) {
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

void Entity::ListAllComponents() const {
    for(auto mapElement: componentTypeMap) {
        cout << "      Component<" << mapElement.first->name() << ">" << endl;
    }
    cout << endl;
}