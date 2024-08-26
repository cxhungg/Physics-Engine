//
// Created by User on 8/4/2024.
//

#include "spring_loop.h"

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

spring_loop::spring_loop() {
    mass = 1.0f;
    velocity = 0.0f;
    damping = 0.1f;
    displacement = 0.0f;
    initialVelocity = 0.0f;

    pause = true;
}

void spring_loop::drawControls() {

    GuiSliderBar((Rectangle){ 50, 20, 200, 20 }, "Mass", TextFormat("%.2f", mass), &mass, 0.1f, 10.0f);
    GuiSliderBar((Rectangle){ 50, 50, 200, 20 }, "Initial Velocity", TextFormat("%.2f", initialVelocity), &initialVelocity, -25.0f, 25.0f);
    GuiSliderBar((Rectangle){ 50, 80, 200, 20 }, "Damping", TextFormat("%.2f", damping), &damping, 0.0f, 1.0f);

}

void spring_loop::startPause() {

    if (GuiButton((Rectangle){ 50, 110, 100, 30 }, pause ? "Start" : "Pause")) {
        pause = !pause;
        if (pause) {
            velocity = 0.0f;
            displacement = 0.0f;
        } else {
            velocity = initialVelocity;
        }
    }
}

void spring_loop::reset() {

    if (GuiButton((Rectangle){ 160, 110, 100, 30 }, "Reset")) {
        pause = true;
        velocity = 0.0f;
        displacement = 0.0f;
    }

}

void spring_loop::update() {

    if (!pause) {
        float acceleration = (-springConstant * displacement - damping * velocity) / mass;
        velocity += acceleration * GetFrameTime() * 28;
        displacement += velocity * GetFrameTime() * 28;
    }

}

void spring_loop::draw() {

    // Draw spring
    Vector2 start = { screenWidth / 2.0f, 0 };
    Vector2 end = { screenWidth / 2.0f, equilibriumY + displacement };
    DrawLineEx(start, end, 4, BLACK);

    // Draw mass
    DrawCircle(screenWidth / 2, equilibriumY + displacement, 20, RED);

}

void spring_loop::displayValues() {

    // Display current values
    DrawText(TextFormat("Mass: %.2f", mass), 30, 180, 20, BLACK);
    DrawText(TextFormat("Velocity: %.2f", velocity), 30, 210, 20, BLACK);
    DrawText(TextFormat("Displacement: %.2f", displacement), 30, 240, 20, BLACK);

}

void spring_loop::render() {

    drawControls();
    startPause();
    reset();
    update();
    draw();

    displayValues();

}
