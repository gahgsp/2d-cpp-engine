//
// Created by Kelvin on 19/06/2020.
//

#ifndef ENGINE2D_COMPONENT_H
#define ENGINE2D_COMPONENT_H

#include "Entity.h"

class Entity;

class Component {
public:
    Entity* owner;
    virtual ~Component() {};
    virtual void Initialize() {};
    virtual void Update(float deltaTime) {};
    virtual void Render() {};
};


#endif //ENGINE2D_COMPONENT_H
