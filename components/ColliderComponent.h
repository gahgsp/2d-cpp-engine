//
// Created by Kelvin on 21/06/2020.
//

#ifndef ENGINE2D_COLLIDERCOMPONENT_H
#define ENGINE2D_COLLIDERCOMPONENT_H

#include "../src/Game.h"
#include "../src/EntityManager.h"
#include "../src/TextureManager.h"

#include "TransformComponent.h"

class ColliderComponent: public Component {
public:
    TransformComponent* transform;
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    bool showColliderBox;
    ColliderComponent(std::string colliderTag, int x, int y, int width, int height);
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
private:
    SDL_Texture* colliderTexture;
};


#endif //ENGINE2D_COLLIDERCOMPONENT_H
