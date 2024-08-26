//
// Created by User on 18/7/2024.
//

#include "ball.h"
#include <cmath>
#include <random>
#include <iostream>

#include "raylib.h"



Ball::Ball(float xPos, float yPos, float radius, Color color) {

    this->xPos = xPos;
    this->yPos = yPos;
    this->radius = radius;
    this->ballColor = color;

    float a = ((float) rand() / (RAND_MAX));

    int sign = (rand() % 2 == 0) ? -1 : 1;

    xVelocity = sign * 10 * a;
    yVelocity = sign * 10 * (1-a);
}

void Ball::move() {

    float xDist = std::abs(xPos-400)+radius;
    float yDist = std::abs(yPos-300)+radius;

    if(pow(xDist,2)+pow(yDist,2) > 62500) {

        // float a = ((float) rand() / (RAND_MAX));
        //
        // xVelocity = (-xVelocity / std::abs(xVelocity)) * 10 * a;
        // yVelocity = (-yVelocity / std::abs(yVelocity)) * 10 * (1-a);
        //
        // std::cout << "this is xvelo: "<< xVelocity << std::endl;
        // std::cout << "this is Y: "<< yVelocity << std::endl;


        // std::random_device rd;
        // std::mt19937 gen(rd());
        // std::uniform_real_distribution<> dis(0.0, 1.0);
        //
        // float a = dis(gen);
        //
        // xVelocity = (-xVelocity / std::abs(xVelocity)) * 10 * a;
        // yVelocity = (-yVelocity / std::abs(yVelocity)) * 10 * (1 - a);
        //
        // std::cout << "This is xVelocity: " << xVelocity << std::endl;
        // std::cout << "This is yVelocity: " << yVelocity << std::endl;

        xPos += xVelocity;
        yPos += yVelocity;

        // Check if the ball is outside the circle
        float distX = xPos - 400;
        float distY = yPos - 300;
        float distance = std::sqrt(distX * distX + distY * distY);

        if (distance + radius > 250) {
            // Calculate the normal vector at the collision point
            float normalX = distX / distance;
            float normalY = distY / distance;

            // Reflect the velocity vector about the normal vector
            float dotProduct = (xVelocity * normalX + yVelocity * normalY);
            xVelocity -= 2 * dotProduct * normalX;
            yVelocity -= 2 * dotProduct * normalY;

            // Move the ball to the edge of the circle to prevent it from getting stuck
            float overlap = (distance + radius) - 250;
            xPos -= overlap * normalX;
            yPos -= overlap * normalY;
        }

    }

    xPos += xVelocity;
    yPos += yVelocity;

}

void Ball::draw() {

    move();

    DrawCircle(xPos,yPos,radius,ballColor);

}

