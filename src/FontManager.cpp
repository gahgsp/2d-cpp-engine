//
// Created by Kelvin on 22/06/2020.
//

#include "FontManager.h"
#include "Game.h"

TTF_Font* FontManager::LoadFont(const char *fontName, int fontSize) {
    return TTF_OpenFont(fontName, fontSize);
}

void FontManager::Draw(SDL_Texture *texture, SDL_Rect position) {
    SDL_RenderCopy(Game::renderer, texture, NULL, &position);
}