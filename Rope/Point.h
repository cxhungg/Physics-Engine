//
// Created by User on 8/5/2024.
//

#ifndef POINT_H
#define POINT_H

#include "raylib.h"

class Point {

public:
    Vector2 position;
    Vector2 oldPosition;
    Vector2 velocity;
    bool isFixed;

    Point(float x, float y, bool fixed = false)
        : position({x, y}), oldPosition({x, y}), velocity({0, 0}), isFixed(fixed) {}

};

#endif //POINT_H
