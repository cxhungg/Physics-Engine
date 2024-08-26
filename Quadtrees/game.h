//
// Created by User on 8/9/2024.
//

#ifndef GAME_H
#define GAME_H


#include <vector>

#include "quadtree.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float BALL_RADIUS = 5.0f;
const int BALLS_PER_CLICK = 1;
const int BALLS_PER_FRAME_HOLD = 2;
const int MAX_BALLS = 1000;

class Game {

public:

    Game();
    Particle createBall(Vector2 position);
    void addBalls(Vector2 position, int count);
    void clear();
    void updateBalls(float deltaTime);

    void mouseInput();

    void render();

    QuadTree quadtree;

    std::vector<Particle> balls;

private:




};


#endif //GAME_H
