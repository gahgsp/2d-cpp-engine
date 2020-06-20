//
// Created by Kelvin on 20/06/2020.
//

#ifndef ENGINE2D_SPRITECOMPONENT_H
#define ENGINE2D_SPRITECOMPONENT_H

#include "../src/Component.h"
#include "TransformComponent.h"

#include "../src/TextureManager.h"
#include "../src/AssetManager.h"
#include "../src/Animation.h"

#include "../include/SDL2/SDL.h"

class SpriteComponent: public Component {
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    bool isAnimated;
    int numberOfFrames;
    int animationSpeed;
    bool isFixed; // Means that the position won't be affected by the camera movement.
    std::map<std::string, Animation> animations;
    std::string currentAnimationName;
    unsigned int currentAnimationIndex = 0;
public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    SpriteComponent(std::string assetTextureName) {
        isAnimated = false;
        isFixed = false;
        SetTexture(assetTextureName);
    }
    SpriteComponent(std::string assetTextureName, int numberOfFrames, int animationSpeed, bool hasDirections, bool isFixed) {
        this->isAnimated = true;
        this->numberOfFrames = numberOfFrames;
        this->animationSpeed = animationSpeed;
        this->isFixed = isFixed;

        if (hasDirections) {
            Animation downAnimation = Animation(0, numberOfFrames, animationSpeed);
            Animation rightAnimation = Animation(1, numberOfFrames, animationSpeed);
            Animation leftAnimation = Animation(2, numberOfFrames, animationSpeed);
            Animation upAnimation = Animation(3, numberOfFrames, animationSpeed);

            animations.emplace("DownAnimation", downAnimation);
            animations.emplace("RightAnimation", rightAnimation);
            animations.emplace("LeftAnimation", leftAnimation);
            animations.emplace("UpAnimation", upAnimation);

            this->currentAnimationIndex = 0;
            this->currentAnimationName = "DownAnimation";
        } else {
            Animation singleAnimation = Animation(0, numberOfFrames, animationSpeed);
            animations.emplace("SingleAnimation", singleAnimation);
            this->currentAnimationIndex = 0;
            this->currentAnimationName = "SingleAnimation";
        }
        PlayAnimation(this->currentAnimationName);
        SetTexture(assetTextureName);
    }
    void PlayAnimation(std::string animationName) {
        numberOfFrames = animations[animationName].numberOfFrames;
        currentAnimationIndex = animations[animationName].index;
        animationSpeed = animations[animationName].animationSpeed;
        currentAnimationName = animationName;
    }
    void SetTexture(std::string assetTextureName) {
        texture = Game::assetManager->GetTexture(assetTextureName);
    }
    void Initialize() override {
        transform = owner->GetComponent<TransformComponent>();
        sourceRectangle.x = 0;
        sourceRectangle.y = 0;
        sourceRectangle.w = transform->width;
        sourceRectangle.h = transform->height;
    }
    void Update(float deltaTime) override {
        if (isAnimated) {
            sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numberOfFrames);
        }
        sourceRectangle.y = currentAnimationIndex * transform->height;

        destinationRectangle.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x);
        destinationRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
        destinationRectangle.w = transform->width * transform->scale;
        destinationRectangle.h = transform->height * transform->scale;
    }
    void Render() override  {
        TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
    }
};


#endif //ENGINE2D_SPRITECOMPONENT_H
