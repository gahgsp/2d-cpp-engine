//
// Created by Kelvin on 20/06/2020.
//

#ifndef ENGINE2D_TILECOMPONENT_H
#define ENGINE2D_TILECOMPONENT_H


#include "../src/Component.h"

#include "../include/SDL2/SDL.h"
#include "../lib/glm/glm.hpp"
#include "../src/TextureManager.h"

class TileComponent: public Component {
public:
    SDL_Texture *texture;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    glm::vec2 position;
    TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string textureTileName){
        texture = Game::assetManager->GetTexture(textureTileName);

        sourceRectangle.x = sourceRectX;
        sourceRectangle.y = sourceRectY;
        sourceRectangle.w = tileSize;
        sourceRectangle.h = tileSize;

        destinationRectangle.x = x;
        destinationRectangle.y = y;
        destinationRectangle.w = tileSize * tileScale;
        destinationRectangle.h = tileSize * tileScale;

        position.x = x;
        position.y = y;
    }
    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }
    void Update(float deltaTime) override {
        // TODO: Here is where we will take take of the tile positions based on the camera movement / position.
    }
    void Render() override {
        TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
    }
};


#endif //ENGINE2D_TILECOMPONENT_H
