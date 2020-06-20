//
// Created by Kelvin on 18/06/2020.
//

#ifndef ENGINE2D_GAME_H
#define ENGINE2D_GAME_H

#define SDL_MAIN_HANDLED

#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "include/SDL2/SDL_ttf.h"

#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"

class Game {
private:
    bool isRunning;
    int ticksLastFrame;
    SDL_Window *window;

public:
    Game();
    ~Game();
    static SDL_Renderer *renderer;
    bool IsRunning() const;
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
    void LoadLevel(int levelIndex);
};


#endif //ENGINE2D_GAME_H
