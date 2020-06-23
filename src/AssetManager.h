//
// Created by Kelvin on 20/06/2020.
//

#ifndef ENGINE2D_ASSETMANAGER_H
#define ENGINE2D_ASSETMANAGER_H


#include <map>
#include "EntityManager.h"

#include "../include/SDL2/SDL_ttf.h"

class AssetManager {
private:
    EntityManager* manager;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
public:
    AssetManager(EntityManager* manager);
    ~AssetManager();
    void Clear();
    void AddTexture(std::string textureName, const char* filePath);
    SDL_Texture* GetTexture(std::string textureName);
    void AddFont(std::string fontName, const char* filePath, int fontSize);
    TTF_Font* GetFont(std::string fontName);
};


#endif //ENGINE2D_ASSETMANAGER_H
