//
// Created by Kelvin on 22/06/2020.
//

#ifndef ENGINE2D_TEXTLABELCOMPONENT_H
#define ENGINE2D_TEXTLABELCOMPONENT_H

#include <SDL2/SDL.h>
#include "../include/SDL2/SDL_ttf.h"

#include "../src/Component.h"
#include "../src/Game.h"
#include "../src/FontManager.h"

class TextLabelComponent: public Component {
private:
    SDL_Rect position;
    std::string text;
    std::string fontFamily;
    SDL_Color color;
    SDL_Texture* texture;
public:
    TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color);
    void SetLabelText(std::string text, std::string fontFamily);
    void Render() override;
};


#endif //ENGINE2D_TEXTLABELCOMPONENT_H
