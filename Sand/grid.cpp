//
// Created by User on 13/7/2024.
//

#include "grid.h"


Grid::Grid(int width, int height) {

    this->baseColor = {0,0,0,0};
    //this->sandColor = {230, 210, 70, 250};
    this->sandColor = {220, 177, 89, 250};
    this->particleSize = 4;
    this->width = width/this->particleSize;
    this->height = height/this->particleSize;

    grid.resize(this->width * this->height, {0, 0, 0, 0});



}

void Grid::clear() {

    std::fill(grid.begin(), grid.end(), baseColor);

}

void Grid::set(int x,int y,Color color) {

    float a = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
    Color b = ColorBrightness(color,a/5);



    if (x >= 0 && x < width && y >= 0 && y < height) {

        if((rand() % 10)%2)
            grid[y * width + x] = b;

        if((rand() % 10)%2)
            grid[y * width + x+1] = b;

        if((rand() % 10)%2)
            grid[y * width + x-1] = b;
        if((rand() % 10)%2)
            grid[(y-1) * width + x] = b;
        if((rand() % 10)%2)
            grid[(y+1) * width + x] = b;
        if((rand() % 10)%2)
            grid[(y-1) * width + x+1] = b;
        if((rand() % 10)%2)
            grid[(y+1) * width + x+1] = b;
        if((rand() % 10)%2)
            grid[(y-1) * width + x-1] = b;
        if((rand() % 10)%2)
            grid[(y+1) * width + x-1] = b;
    }

}

void Grid::swap(int a, int b) {


    Color temp = grid[a];
    grid[a] = grid[b];
    grid[b] = temp;

}

bool Grid::isEmpty(int index) {
    return ColorToInt(grid[index]) == ColorToInt({0,0,0,0});
}

Color Grid::getSandColor() {
    return sandColor;
}

int Grid::getParticleSize() {
    return particleSize;
}

void Grid::update() {

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        clear();
        std::cout << "cleared" << std::endl;
    }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        int x = mousePos.x / particleSize;
        int y = mousePos.y / particleSize;



        set(x, y, sandColor);
    }

    for (int i = width * height - 1; i >= 0; i--) {
        updatePixel(i);
    }

}


void Grid::updatePixel(int i) {

    int below = i + width;
    int belowLeft = below - 1;
    int belowRight = below + 1;

    if (below < width * height && isEmpty(below)) {
        swap(i, below);
    } else if (belowLeft < width * height && isEmpty(belowLeft)) {
        swap(i, belowLeft);
    } else if (belowRight < width * height && isEmpty(belowRight)) {
        swap(i, belowRight);
    }

    // for (int y = 0; y < height/particleSize-1; y++) {
    //     for (int x = 0; x < width/particleSize; x++) {
    //         int index = y * width + x;
    //
    //         if(ColorToInt(gridArray[index]) == ColorToInt(sandColor)) {
    //
    //             if(isEmpty(index+width/particleSize)) {
    //
    //                 swap(index,index+width/particleSize);
    //             }
    //         }
    //     }
    // }
}

void Grid::draw() {

    update();

    ClearBackground({44, 44, 127, 255});

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color color = grid[y * width + x];
            if (color.a != 0) {
                DrawRectangle(x * particleSize, y * particleSize, particleSize, particleSize, color);
            }
        }
    }


}

