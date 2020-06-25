//
// Created by Kelvin on 21/06/2020.
//

#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(std::string colliderTag, int x, int y, int width, int height) {
    this->colliderTag = colliderTag;
    this->collider = {x, y, width, height};
    this->showColliderBox = false;
    this->colliderTexture = Game::assetManager->GetTexture("Collider-Box");
}

void ColliderComponent::Initialize() {
    if (owner->HasComponent<TransformComponent>()) {
        transform = owner->GetComponent<TransformComponent>();
        sourceRectangle = {0, 0, transform->width, transform->height};
        destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
    }
}

void ColliderComponent::Update(float deltaTime) {
    if (Game::event.type == SDL_KEYDOWN) {
        // If the C key was pressed.
        // TODO: Maybe create a DEBUG profile and make these variables all Game Static!
        if (std::to_string(Game::event.key.keysym.sym) == "99") {
            showColliderBox = !showColliderBox;
        }
    }

    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;

    destinationRectangle.x = collider.x - Game::camera.x;
    destinationRectangle.y = collider.y - Game::camera.y;
}

void ColliderComponent::Render() {
    if (showColliderBox) {
        TextureManager::Draw(colliderTexture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
    }
}