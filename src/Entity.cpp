//
// Created by Kelvin on 19/06/2020.
//

#include <iostream>

#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(EntityManager &manager): manager(manager) {
    this->isActive = true;
}

Entity::Entity(EntityManager &manager, std::string name, LayerType layer): manager(manager), name(name), layer(layer) {
    this->isActive = true;
}

void Entity::Update(float deltaTime) {
    for (auto& component: components) {
        component->Update(deltaTime);
    }
}

void Entity::Render() {
    for (auto& component: components) {
        component->Render();
    }
}

void Entity::Destroy() {
    this->isActive = false;
}

bool Entity::IsActive() const {
    return isActive;
}

void Entity::ListAllComponents() const {
    for (auto component : componentsTypes) {
        std::cout << "Component<" << component.first->name() << ">" << std::endl;
    }
}