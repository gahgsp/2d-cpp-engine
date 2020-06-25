//
// Created by Kelvin on 20/06/2020.
//

#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string assetTextureName) {
    isAnimated = false;
    isFixed = false;
    SetTexture(assetTextureName);
}

SpriteComponent::SpriteComponent(std::string assetTextureName, int numberOfFrames, int animationSpeed,
                                 bool hasDirections, bool isFixed) {
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

void SpriteComponent::PlayAnimation(std::string animationName) {
    numberOfFrames = animations[animationName].numberOfFrames;
    currentAnimationIndex = animations[animationName].index;
    animationSpeed = animations[animationName].animationSpeed;
    currentAnimationName = animationName;
}

void SpriteComponent::SetTexture(std::string assetTextureName) {
    texture = Game::assetManager->GetTexture(assetTextureName);
}

void SpriteComponent::Initialize() {
    transform = owner->GetComponent<TransformComponent>();
    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    sourceRectangle.w = transform->width;
    sourceRectangle.h = transform->height;
}

void SpriteComponent::Update(float deltaTime) {
    if (isAnimated) {
        sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numberOfFrames);
    }
    sourceRectangle.y = currentAnimationIndex * transform->height;

    destinationRectangle.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x);
    destinationRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
    destinationRectangle.w = transform->width * transform->scale;
    destinationRectangle.h = transform->height * transform->scale;
}

void SpriteComponent::Render() {
    TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
}