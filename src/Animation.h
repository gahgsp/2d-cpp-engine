//
// Created by Kelvin on 20/06/2020.
//

#ifndef ENGINE2D_ANIMATION_H
#define ENGINE2D_ANIMATION_H


class Animation {
public:
    unsigned int index;
    unsigned int numberOfFrames;
    unsigned int animationSpeed;
    Animation();
    Animation(unsigned int index, unsigned int numberOfFrames, unsigned int animationSpeed);
};


#endif //ENGINE2D_ANIMATION_H
