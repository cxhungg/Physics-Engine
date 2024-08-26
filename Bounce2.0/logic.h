//
// Created by User on 17/7/2024.
//

#ifndef LOGIC_H
#define LOGIC_H


#include <vector>

#include "ball.h"



class Logic{

public:

    Logic();

    void move();

    void draw();
    void addBlock(int xPos, int yPos, int width, int height, int velocity, Color color);

    void addBall(float xPos, float yPos, float radius, Color color);

    int getVectorSize();

    void clear();

    void clickToAdd();

private:


    std::vector<Ball> balls;
};



#endif //LOGIC_H
