//
// Created by User on 8/9/2024.
//

#include "particle.h"

#include <vector>

Particle::Particle(Vector2 position) {

    this->position = position;
    velocity = {(float)GetRandomValue(-200, 200) / 100.0f, (float)GetRandomValue(-200, 200) / 100.0f};
    color = {(unsigned char)GetRandomValue(50, 255), (unsigned char)GetRandomValue(50, 255), (unsigned char)GetRandomValue(50, 255), 255};

}

// Color Particle::coolColors() {
//
//     std::vector<Color> niceColors = {
//         {255, 0, 0, 255},    // Red
//         {0, 255, 0, 255},    // Green
//         {0, 0, 255, 255},    // Blue
//         {255, 165, 0, 255},  // Orange
//         {0, 255, 255, 255},  // Cyan
//         {128, 0, 128, 255},  // Purple
//         {255, 255, 0, 255}   // Yellow
//     };
//
//     // Randomly select a color from the predefined list
//     int randomIndex = GetRandomValue(0, niceColors.size() - 1);
//     return niceColors[randomIndex];
// }