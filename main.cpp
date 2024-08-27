//
// Created by User on 17/7/2024.
//
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "RayGui/raygui.h"

#include "Sand/grid.h"

#include "Bounce2.0/logic.h"
#include "ProjectileMotion/projectile.h"
#include "Planets/System.h"
#include "Quadtrees/game.h"
#include "Circle_Collision/circle_loop.h"

#include "Spring/spring_loop.h"
#include "Rope/Rope.h"

#include <memory>

#include <iostream>



int main()
{

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Physics Engine!");
    SetTargetFPS(60);

    bool mainFlag = true;

    bool ballFlag = false;
    bool springFlag = false;
    bool sandFlag = false;

    bool springSimulation = false;
    bool ropeSimulation = false;

    bool bouncingBalls = false;
    bool bouncing2 = false;
    bool collidingBalls = false;
    bool projectileMotion = false;
    bool celestialBodies = false;
    bool collision2 = false;

    //Grid sand(screenWidth,screenHeight);
    //Logic bounce2;

    std::unique_ptr<Logic> bounce2;
    std::unique_ptr<Grid> sand;
    std::unique_ptr<Projectile> projectile;
    std::unique_ptr<System> planet;
    std::unique_ptr<Game> quadtree;
    std::unique_ptr<circle_loop> circle;


    std::unique_ptr<spring_loop> spring;
    std::unique_ptr<Rope> rope;

    int n;

    while (!WindowShouldClose())
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground({214, 194, 139,255});


        GuiSetStyle(DEFAULT, TEXT_SIZE, 10);

        if(mainFlag) {
            DrawText("Hung's Physics Engine", 285, 100, 20, {63, 94, 204,255});

            if(GuiButton((Rectangle){350, 180, 100, 30}, "Balls")) {

                mainFlag = false;
                ballFlag = true;

                n = 0;

            }

            if(GuiButton((Rectangle){350, 230, 100, 30}, "Springs")) {

                mainFlag = false;
                springFlag = true;


                n = 0;
            }

            if(GuiButton((Rectangle){350, 280, 100, 30}, "Sand")) {

                mainFlag = false;
                sandFlag = true;

                sand = std::make_unique<Grid>(screenWidth,screenHeight);

            }
        }

        if(ballFlag) {


            DrawText("Hung's Physics Engine", 285, 100, 20, {63, 94, 204,255});

            GuiSetStyle(DEFAULT, TEXT_SIZE, 10);

            if(!n) {
                guiState = STATE_DISABLED;
            } else {
                guiState = STATE_NORMAL;
            }

            if(GuiButton((Rectangle){280, 180, 100, 30}, "Bouncing Balls")) {
                ballFlag = false;
                bouncingBalls = true;

            }

            if(GuiButton((Rectangle){420, 230, 100, 30}, "Bouncing V_2.0")) {

                ballFlag = false;
                bouncing2 = true;

                bounce2 = std::make_unique<Logic>(); // Create the Logic object here
            }

            if(GuiButton((Rectangle){280, 280, 100, 30}, "Colliding Balls")) {
                ballFlag = false;
                collidingBalls = true;

                circle = std::make_unique<circle_loop>();

            }

            if(GuiButton((Rectangle){420, 180, 100, 30}, "Projectile Motion")) {
                ballFlag = false;
                projectileMotion = true;

               projectile = std::make_unique<Projectile>(); // Create the Logic object here
            }

            if(GuiButton((Rectangle){280, 230, 100, 30}, "Celestial Bodies")) {
                ballFlag = false;
                celestialBodies = true;

                planet = std::make_unique<System>();
            }

            if(GuiButton((Rectangle){420, 280, 100, 30}, "Collision V_2.0")) {
                ballFlag = false;
                collision2 = true;

                quadtree = std::make_unique<Game>();

            }

            if(GuiButton((Rectangle){ 24, 24, 100, 30 }, "#56#Back")) {

                ballFlag = false;
                mainFlag = true;


            }
            n = 1;
        }

        if(springFlag) {

            DrawText("Hung's Physics Engine", 285, 100, 20, {63, 94, 204,255});

            if(!n) {
                guiState = STATE_DISABLED;
            } else {
                guiState = STATE_NORMAL;
            }

            if(GuiButton((Rectangle){350, 200, 100, 30}, "Spring")) {


                springFlag = false;
                springSimulation = true;


                spring = std::make_unique<spring_loop>();
            }


            if(GuiButton((Rectangle){350, 250, 100, 30}, "Rope")) {


                springFlag = false;
                ropeSimulation = true;
                rope = std::make_unique<Rope>(screenWidth / 2, 50);
            }


            if(GuiButton((Rectangle){ 24, 24, 100, 30 }, "#56#Back")) {

                springFlag = false;
                mainFlag = true;


            }


            n = 1;

        }

        if(sandFlag) {


            DrawText("Sand Simulation", 323, 100, 20, {212, 185, 112,255});


            SetTargetFPS(140);
            sand->draw();

            if(GuiButton((Rectangle){ 24, 24, 100, 30 }, "#56#Back")) {

                sandFlag = false;
                mainFlag = true;
                //sand->clear();
                SetTargetFPS(60);

            }

        }

        if(bouncingBalls) {

            if(GuiButton((Rectangle){ 24, 24, 100, 30 }, "#56#Back")) {

                ballFlag = true;
                bouncingBalls = false;
            }

        }

        if(bouncing2) {

            if(GuiButton((Rectangle){ 24, 24, 100, 30 }, "#56#Back")) {

                ballFlag = true;
                bouncing2 = false;

                bounce2->clear();

            }

            bounce2->draw();


        }

        if(collidingBalls) {

            if(GuiButton((Rectangle){ 24, 24, 100, 30 }, "#56#Back")) {

                ballFlag = true;
                collidingBalls = false;


            }

            circle->render();
        }

        if(projectileMotion) {
            if(GuiButton((Rectangle){ 674, 24, 100, 30 }, "#56#Back")) {

                ballFlag = true;
                projectileMotion = false;



            }

            projectile->draw();

        }

        if(celestialBodies) {

            if(GuiButton((Rectangle){ 676, 546, 100, 30 }, "#56#Back")) {

                ballFlag = true;
                celestialBodies = false;


            }

            planet->draw();
        }

        if(collision2) {

            quadtree->render();

            if(GuiButton((Rectangle){ 674, 24, 100, 30 }, "#56#Back")) {

                ballFlag = true;
                collision2 = false;

            }



        }


        if(springSimulation) {

            if(GuiButton((Rectangle){ 674, 24, 100, 30 }, "#56#Back")) {

                springFlag = true;
                springSimulation = false;

            }
            spring->render();
        }

        if(ropeSimulation) {

            if(GuiButton((Rectangle){ 24, 24, 100, 30 }, "#56#Back")) {

                springFlag = true;
                ropeSimulation = false;

            }
            rope->render();
        }

        // if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "#191#Show Message")) showMessageBox = true;
        //
        // if (showMessageBox)
        // {
        //     int result = GuiMessageBox((Rectangle){ 85, 70, 250, 100 },
        //         "#191#Message Box", "Hi! This is a message!", "Nice;Cool");
        //
        //     if (result >= 0) showMessageBox = false;
        // }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
