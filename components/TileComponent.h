//
// Created by Kelvin on 20/06/2020.
//

#ifndef ENGINE2D_TILECOMPONENT_H
#define ENGINE2D_TILECOMPONENT_H

#include "../include/SDL2/SDL.h"

#include "../src/Component.h"
#include "../src/TextureManager.h"

#include "../lib/glm/glm.hpp"

class TileComponent: public Component {
public:
    SDL_Texture *texture;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    glm::vec2 position;
    TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string textureTileName);
    ~TileComponent();
    void Update(float deltaTime) override;
    void Render() override;
};


#endif //ENGINE2D_TILECOMPONENT_H
