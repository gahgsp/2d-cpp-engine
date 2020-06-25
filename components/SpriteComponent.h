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
    SpriteComponent(std::string assetTextureName);
    SpriteComponent(std::string assetTextureName, int numberOfFrames, int animationSpeed, bool hasDirections, bool isFixed);
    void PlayAnimation(std::string animationName);
    void SetTexture(std::string assetTextureName);
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
};


#endif //ENGINE2D_SPRITECOMPONENT_H
