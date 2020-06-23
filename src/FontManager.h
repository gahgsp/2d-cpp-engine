//
// Created by Kelvin on 22/06/2020.
//

#ifndef ENGINE2D_FONTMANAGER_H
#define ENGINE2D_FONTMANAGER_H


#include "../include/SDL2/SDL_ttf.h"

class FontManager {
public:
    static TTF_Font* LoadFont(const char* fontName, int fontSize);
    static void Draw(SDL_Texture* texture, SDL_Rect position);
};


#endif //ENGINE2D_FONTMANAGER_H
