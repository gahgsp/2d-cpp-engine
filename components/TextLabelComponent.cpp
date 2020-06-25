//
// Created by Kelvin on 22/06/2020.
//

#include "TextLabelComponent.h"

TextLabelComponent::TextLabelComponent(int x, int y, std::string text, std::string fontFamily,
                                       const SDL_Color &color) {
    this->position.x = x;
    this->position.y = y;
    this->text = text;
    this->fontFamily = fontFamily;
    this->color = color;
    SetLabelText(text, fontFamily);
}

void TextLabelComponent::SetLabelText(std::string text, std::string fontFamily) {
    SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->GetFont(fontFamily), text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
}

void TextLabelComponent::Render() {
    FontManager::Draw(texture, position);
}