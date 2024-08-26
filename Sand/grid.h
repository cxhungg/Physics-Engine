//
// Created by User on 13/7/2024.
//

#ifndef GRID_H
#define GRID_H

#include <raylib.h>
#include <vector>
#include <iostream>
#include <random>

class Grid {

public:

    Grid(int width, int height);


    void clear();
    void set(int x, int y, Color color);
    void swap(int a, int b);
    bool isEmpty(int index);

    Color getSandColor();
    int getParticleSize();

    void update();

    void draw();


private:

    void updatePixel(int i);

    int particleSize;
    int width;
    int height;

    std::vector<Color> grid;

    Color baseColor;
    Color sandColor;


};



#endif //GRID_H
