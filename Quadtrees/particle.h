//
// Created by User on 8/9/2024.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

class Particle {

public:

    Particle(Vector2 position);
    // Color coolColors();
    Vector2 position;
    Vector2 velocity;
    Color color;

};



#endif //PARTICLE_H
