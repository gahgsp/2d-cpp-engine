//
// Created by Kelvin on 19/06/2020.
//

#ifndef ENGINE2D_ENTITY_H
#define ENGINE2D_ENTITY_H

#include <vector>
#include <string>
#include <map>

#include "EntityManager.h"
#include "Component.h"

class EntityManager;
class Component;

class Entity {
private:
    EntityManager& manager;
    bool isActive;
    std::vector<Component*> components;
    std::map<const std::type_info*, Component*> componentsTypes;
public:
    std::string name;
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string name);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    bool IsActive() const;

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args) {
        T* newComponent(new T(std::forward<TArgs>(args)...));
        newComponent->owner = this;
        components.emplace_back(newComponent);
        componentsTypes[&typeid(*newComponent)] = newComponent;
        newComponent->Initialize();
        return *newComponent;
    }

    template <typename T>
    T* GetComponent() {
        return static_cast<T*>(componentsTypes[&typeid(T)]);
    }
};


#endif //ENGINE2D_ENTITY_H