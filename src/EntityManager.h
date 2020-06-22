//
// Created by Kelvin on 19/06/2020.
//

#ifndef ENGINE2D_ENTITYMANAGER_H
#define ENGINE2D_ENTITYMANAGER_H

#include <vector>

#include "Component.h"
#include "Entity.h"

class Entity;

class EntityManager {
private:
    std::vector<Entity*> entities;
public:
    void Clear();
    void Update(float deltaTime);
    void Render();
    bool HasNoEntities() const;
    Entity& AddEntity(std::string entityName, LayerType layer);
    std::vector<Entity*> GetEntities() const;
    std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
    unsigned int GetEntityCount() const;
    void ListAllEntities() const;
    CollisionType CheckCollisions() const;
};


#endif //ENGINE2D_ENTITYMANAGER_H
