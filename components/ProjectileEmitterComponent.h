//
// Created by Kelvin on 23/06/2020.
//

#ifndef ENGINE2D_PROJECTILEEMITTERCOMPONENT_H
#define ENGINE2D_PROJECTILEEMITTERCOMPONENT_H


#include "../src/Component.h"
#include "../lib/glm/glm.hpp"
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
    ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldLoop) {
        this->speed = speed;
        this->angleRad = glm::radians(static_cast<float>(angleDeg));
        this->range = range;
        this->shouldLoop = shouldLoop;
    }
    void Initialize() override {
        transform = owner->GetComponent<TransformComponent>();
        origin = glm::vec2(transform->position.x, transform->position.y);
        transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
    }
    void Update(float deltaTime) override {
        if (glm::distance(transform->position, origin) > range) {
            if (shouldLoop) {
                transform->position = origin;
            } else {
                owner->Destroy();
            }
        }
    }
};


#endif //ENGINE2D_PROJECTILEEMITTERCOMPONENT_H
