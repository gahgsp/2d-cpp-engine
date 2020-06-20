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
    KeyboardComponent() {}
    KeyboardComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey) {
        this->upKey = GetSDLKeyStringCode(upKey);
        this->rightKey = GetSDLKeyStringCode(rightKey);
        this->downKey = GetSDLKeyStringCode(downKey);
        this->leftKey = GetSDLKeyStringCode(leftKey);
        this->shootKey = GetSDLKeyStringCode(shootKey);
    }
    std::string GetSDLKeyStringCode(std::string key) {
        if (key.compare("up") == 0) return "1073741906";
        if (key.compare("down") == 0) return "1073741905";
        if (key.compare("left") == 0) return "1073741904";
        if (key.compare("right") == 0) return "1073741903";
        if (key.compare("space") == 0) return "32";
        return std::to_string(static_cast<int>(key[0]));
    }
    void Initialize() override {
        transform = owner->GetComponent<TransformComponent>();
        sprite = owner->GetComponent<SpriteComponent>();
    }
    void Update(float deltaTime) override {
        if (Game::event.type == SDL_KEYDOWN) {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);
            if (keyCode.compare(upKey) == 0) {
                transform->velocity.y = -50;
                transform->velocity.x = 0;
                sprite->PlayAnimation("UpAnimation");
            }
            if (keyCode.compare(rightKey) == 0) {
                transform->velocity.y = 0;
                transform->velocity.x = 50;
                sprite->PlayAnimation("RightAnimation");
            }
            if (keyCode.compare(downKey) == 0) {
                transform->velocity.y = 50;
                transform->velocity.x = 0;
                sprite->PlayAnimation("DownAnimation");
            }
            if (keyCode.compare(leftKey) == 0) {
                transform->velocity.y = 0;
                transform->velocity.x = -50;
                sprite->PlayAnimation("LeftAnimation");
            }
            if (keyCode.compare(shootKey) == 0) {
                // TODO: Implement shoot projectile when shoot key is pressed.
            }
        }

        if (Game::event.type == SDL_KEYUP) {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);
            if (keyCode.compare(upKey) == 0) {
                transform->velocity.y = 0;
            }
            if (keyCode.compare(rightKey) == 0) {
                transform->velocity.x = 0;
            }
            if (keyCode.compare(downKey) == 0) {
                transform->velocity.y = 0;
            }
            if (keyCode.compare(leftKey) == 0) {
                transform->velocity.x = 0;
            }
            if (keyCode.compare(shootKey) == 0) {
                // TODO: Implement shoot projectile when shoot key is released.
            }
        }
    }
};


#endif //ENGINE2D_KEYBOARDCOMPONENT_H
