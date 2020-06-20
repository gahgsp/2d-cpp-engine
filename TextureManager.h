//
// Created by Kelvin on 20/06/2020.
//

#ifndef ENGINE2D_TEXTUREMANAGER_H
#define ENGINE2D_TEXTUREMANAGER_H

#include "Game.h"

class Game;

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip);
};


#endif //ENGINE2D_TEXTUREMANAGER_H
