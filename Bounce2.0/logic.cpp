//
// Created by User on 17/7/2024.
//

#include "logic.h"
#include <sstream>

Logic:: Logic(){

    addBall(400,200,10,YELLOW);
    addBall(200,300,10,BLUE);
}

void Logic::move() {


    for (auto& ball : balls) {
        ball.move();
    }

}

void Logic::draw() {

    ClearBackground({44, 44, 127, 255});

    DrawCircle(400,300,250,{23, 23, 79,255});

    clickToAdd();

    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        balls.clear();
    }

    std::ostringstream oss;
    oss << "Num of Balls: " << balls.size();
    DrawText(oss.str().c_str(), 325, 100, 20, {63, 94, 204,255});

    for (auto& ball : balls) {
        ball.draw();
    }
    //DrawFPS(10, 10);

}


void Logic::addBall(float xPos, float yPos, float radius, Color color) {

    balls.emplace_back(xPos,yPos,radius,color);

}

int Logic::getVectorSize() {
    return balls.size();
}

void Logic::clear() {

        balls.clear();
}

void Logic::clickToAdd() {

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        addBall(GetMouseX(),GetMouseY(),10,RAYWHITE);


    }

}


