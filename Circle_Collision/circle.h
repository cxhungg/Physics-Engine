//
// Created by User on 8/26/2024.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include "raylib.h"
#include <vector>

class Circle {

public:
    Circle(Vector2 position,Vector2 velocity,Color color):position(position), velocity(velocity),color(color){};


    Vector2 position;
    Vector2 velocity;
    Color color;

};



#endif //CIRCLE_H
