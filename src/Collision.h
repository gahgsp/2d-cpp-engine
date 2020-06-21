//
// Created by Kelvin on 21/06/2020.
//

#ifndef ENGINE2D_COLLISION_H
#define ENGINE2D_COLLISION_H


#include "../include/SDL2/SDL.h"

class Collision {
public:
    static bool CheckRectangleCollision(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB);
};


#endif //ENGINE2D_COLLISION_H
