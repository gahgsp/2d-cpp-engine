//
// Created by Kelvin on 20/06/2020.
//

#ifndef ENGINE2D_SPRITECOMPONENT_H
#define ENGINE2D_SPRITECOMPONENT_H

#include "../src/Component.h"
#include "TransformComponent.h"

#include "../src/TextureManager.h"
#include "../src/AssetManager.h"

#include "../include/SDL2/SDL.h"

class SpriteComponent: public Component {
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    SpriteComponent(const char* filePath) {
        SetTexture(filePath);
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
        destinationRectangle.x = (int) transform->position.x;
        destinationRectangle.y = (int) transform->position.y;
        destinationRectangle.w = transform->width * transform->scale;
        destinationRectangle.h = transform->height * transform->scale;
    }
    void Render() override  {
        TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
    }
};


#endif //ENGINE2D_SPRITECOMPONENT_H
