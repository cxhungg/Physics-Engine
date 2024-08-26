//
// Created by User on 20/7/2024.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H

// #include "raylib.h"
// #define RAYGUI_IMPLEMENTATION
// #include "raygui.h"


#include <cmath>
#include <sstream>

class Projectile {

public:
    Projectile() {
        screenHeight = 600;
        screenWidth = 800;

        initialX = 100;
        initialY = 550;

        position = {initialX, initialY};

        velocity = {0,0};
        radius = 10;

        isMoving = false;
        maxHeight = 0;
        distance = 0;
        time = 0;

        inputComplete = false;
        showResults = false;

        velocityEdit = false;
        angleEdit = false;

        circleTexture = LoadTexture("../Resources/projectile_blue.png");

        strcpy(massInput, "100.0");
        strcpy(heightInput, "0.0");
        strcpy(velocityInput, "");
        strcpy(angleInput, "");
    }

    void input() {

        GuiSetStyle(TEXTBOX, BORDER_COLOR_NORMAL, ColorToInt(PINK));
        GuiSetStyle(TEXTBOX, TEXT, ColorToInt(PINK));
        GuiSetStyle(LABEL, TEXT, ColorToInt(PINK));

        GuiLabel((Rectangle){20, 20, 200, 20}, "Enter Ball's Mass:");
        GuiTextBox((Rectangle){220, 20, 100, 20}, massInput, 10, false);

        GuiLabel((Rectangle){20, 60, 200, 20}, "Enter Ball's Height:");
        GuiTextBox((Rectangle){220, 60, 100, 20}, heightInput, 10, false);

        GuiLabel((Rectangle){20, 100, 200, 20}, "Enter Initial Velocity:");
        if(GuiTextBox((Rectangle){220, 100, 100, 20}, velocityInput, 10, velocityEdit)) {
            velocityEdit = !velocityEdit;
        }

        GuiLabel((Rectangle){20, 140, 200, 20}, "Enter Angle:");
        if(GuiTextBox((Rectangle){220, 140, 100, 20}, angleInput, 10, angleEdit)) {

            angleEdit = !angleEdit;
        }
    }

    void enter() {

        mass = atof(massInput);
        height = atof(heightInput);
        initialVelocity = atof(velocityInput);
        angle = atof(angleInput) * (PI / 180.0f); // Convert to radians



        position = {100, screenHeight - 50 - height};
        velocity = {initialVelocity * cos(angle), -initialVelocity * sin(angle)};
        isMoving = true;
        maxHeight = height;
        distance = 0;
        time = 0;
        inputComplete = true;
    }

    void moving() {

        float dt = GetFrameTime() * 5;
        time += dt;
        velocity.y += 9.8f * dt; // Gravity
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        if (position.y >= screenHeight - 50) {
            position.y = screenHeight - 50;
            isMoving = false;
            showResults = true;
        }

        if (position.y < screenHeight - 50 - maxHeight) {
            maxHeight = screenHeight - 50 - position.y;
        }

        distance = position.x - 100;
    }

    void update() {


        if (!inputComplete) {

            input();

            if(GuiButton((Rectangle){220, 190, 100, 30}, "Enter")) {

                enter();
            }
        } else if(isMoving){

            moving();

        }
    }

    void stats() {


        std::ostringstream oss;
        oss << "Distance: " << distance << " m\n";
        //oss << "Distance: " << finalball.dist_travelled() << " m\n";
        oss << "Time: " << time << " s\n";
        //oss << "Time: " << finalball.air_time() << " s\n";
        oss << "Max Height: " << maxHeight << " m";
        //oss << "Max Height: " <<  << " m";
        DrawText(oss.str().c_str(), 15, 15, 20, {63, 94, 204,255});

        if(GuiButton((Rectangle){420, 230, 100, 30}, "Another one")) {

            inputComplete = false;
            showResults = false;

            position.x = initialX;
            position.y = initialY;

            strcpy(velocityInput, "");
            strcpy(angleInput, "");

        }
    }

    void draw() {


        update();

        ClearBackground({44, 44, 127, 255});

        DrawRectangle(0, screenHeight - 50, screenWidth, 50, {23, 23, 79,255});

        //DrawCircleV(position, radius, RED);

        Vector2 texturePos = position;
        texturePos.x -= radius;
        texturePos.y -= radius;

        DrawTextureV(circleTexture,texturePos,WHITE);

        if(showResults) {

            stats();
        }
    }

private:

    float initialX;
    float initialY;

    Vector2 position;
    Vector2 velocity;
    float radius;
    bool isMoving;
    float maxHeight;
    float distance;
    float time;

    bool inputComplete;
    bool showResults;

    bool velocityEdit;
    bool angleEdit;

    float mass;
    float height;
    float initialVelocity;
    float angle;

    Texture2D circleTexture;

    char massInput[10];
    char heightInput[10];
    char velocityInput[10];
    char angleInput[10];

    int screenHeight;
    int screenWidth;

};



#endif //PROJECTILE_H
