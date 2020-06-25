//
// Created by Kelvin on 23/06/2020.
//

#ifndef ENGINE2D_PROJECTILEEMITTERCOMPONENT_H
#define ENGINE2D_PROJECTILEEMITTERCOMPONENT_H

#include "../lib/glm/glm.hpp"

#include "../src/Component.h"

#include "TransformComponent.h"

class ProjectileEmitterComponent: public Component {
private:
    TransformComponent* transform;
    glm::vec2 origin;
    int speed;
    float angleRad;
    int range;
    bool shouldLoop;
public:
    ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldLoop);
    void Initialize() override;
    void Update(float deltaTime) override;
};


#endif //ENGINE2D_PROJECTILEEMITTERCOMPONENT_H
