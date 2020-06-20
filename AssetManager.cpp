//
// Created by Kelvin on 20/06/2020.
//

#include "AssetManager.h"
#include "TextureManager.h"

AssetManager::AssetManager(EntityManager *manager): manager(manager) {}

void AssetManager::Clear() {
    textures.clear();
}

void AssetManager::AddTexture(std::string textureName, const char *filePath) {
    textures.emplace(textureName, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureName) {
    return textures[textureName];
}