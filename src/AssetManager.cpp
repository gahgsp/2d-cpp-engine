//
// Created by Kelvin on 20/06/2020.
//

#include "AssetManager.h"
#include "TextureManager.h"
#include "FontManager.h"

AssetManager::AssetManager(EntityManager *manager): manager(manager) {}

void AssetManager::Clear() {
    textures.clear();
    fonts.clear();
}

void AssetManager::AddTexture(std::string textureName, const char *filePath) {
    textures.emplace(textureName, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureName) {
    return textures[textureName];
}

void AssetManager::AddFont(std::string fontName, const char *filePath, int fontSize) {
    fonts.emplace(fontName, FontManager::LoadFont(filePath, fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontName) {
    return fonts[fontName];
}
