//
// Created by Kelvin on 20/06/2020.
//

#ifndef ENGINE2D_ASSETMANAGER_H
#define ENGINE2D_ASSETMANAGER_H


#include <map>
#include <SDL2/SDL_render.h>
#include "EntityManager.h"

class AssetManager {
private:
    EntityManager* manager;
    std::map<std::string, SDL_Texture*> textures;
public:
    AssetManager(EntityManager* manager);
    ~AssetManager();
    void Clear();
    void AddTexture(std::string textureName, const char* filePath);
    SDL_Texture* GetTexture(std::string textureName);
};


#endif //ENGINE2D_ASSETMANAGER_H
