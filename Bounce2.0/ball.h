//
// Created by User on 18/7/2024.
//

#ifndef BALL_H
#define BALL_H

#include "raylib.h"

class Ball {

    public:
        Ball(float xPos, float yPos, float radius, Color color);


        void move();

        void draw();

    private:

        float xPos;
        float yPos;
        float radius;

        float xVelocity;
        float yVelocity;

        Color ballColor;
    };


#endif //BALL_H
