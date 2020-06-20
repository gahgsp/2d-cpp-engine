//
// Created by Kelvin on 20/06/2020.
//

#include "Animation.h"

Animation::Animation() {}

Animation::Animation(unsigned int index, unsigned int numberOfFrames, unsigned int animationSpeed) {
    this->index = index;
    this->numberOfFrames = numberOfFrames;
    this->animationSpeed = animationSpeed;
}