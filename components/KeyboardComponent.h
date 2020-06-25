//
// Created by Kelvin on 20/06/2020.
//

#ifndef ENGINE2D_KEYBOARDCOMPONENT_H
#define ENGINE2D_KEYBOARDCOMPONENT_H

#include "../src/Component.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"

class KeyboardComponent: public Component {
public:
    std::string upKey;
    std::string downKey;
    std::string rightKey;
    std::string leftKey;
    std::string shootKey;
    TransformComponent* transform;
    SpriteComponent* sprite;
    KeyboardComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey);
    std::string GetSDLKeyStringCode(std::string key);
    void Initialize() override;
    void Update(float deltaTime) override;
};


#endif //ENGINE2D_KEYBOARDCOMPONENT_H
