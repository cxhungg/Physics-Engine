//
// Created by User on 8/5/2024.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include "Body.h"


class System {
public:
    System() {
        camera.position = (Vector3){30.0f, 20.0f, 30.0f};
        camera.target = (Vector3){0.0f, 0.0f, 0.0f};
        camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;

        bodies.emplace_back(0, 1.0f, YELLOW, 0, "Sun");

        bodies.emplace_back(5, 0.4f, BLUE, 1.0f, "Mercury");
        bodies.emplace_back(8, 0.6f, RED, 0.8f, "Venus");
        bodies.emplace_back(11, 0.5f, GREEN, 0.6f, "Earth");
    }

    void update() {
        float deltaTime = GetFrameTime();
        for (auto &body: bodies) {
            body.Update(deltaTime);
        }
    }

    void drawPlanets() {
        ClearBackground(BLACK);


        BeginMode3D(camera);
        for (auto &body: bodies) {
            body.DrawOrbit();
            body.Draw();
        }
        EndMode3D();
        DrawTexture(circleTexture,(screenWidth/2)-27,(screenHeight/2)-26,WHITE);
    }


    void guiPanel() {
        if (GuiButton((Rectangle){20, 20, 120, 30}, "Add Planet")) {
            showAddPlanetPanel = true;
        }

        if (showAddPlanetPanel) {
            GuiPanel((Rectangle){20, 75, 280, 400}, "Add New Planet");
            GuiTextBox((Rectangle){76, 105, 180, 30}, nameInput, 10, true);
            GuiSlider((Rectangle){76, 145, 180, 20}, "Distance", TextFormat("%.1f", orbitRadiusInput),
                      &orbitRadiusInput, 3.0f, 20.0f);
            GuiSlider((Rectangle){76, 175, 180, 20}, "Size", TextFormat("%.2f", radiusInput), &radiusInput, 0.1f, 1.0f);
            GuiSlider((Rectangle){76, 205, 180, 20}, "Speed", TextFormat("%.2f", speedInput), &speedInput, 0.1f, 2.0f);
            GuiColorPicker((Rectangle){76, 235, 180, 180}, "Color", &colorInput);

            if (GuiButton((Rectangle){76, 425, 180, 30}, "Add")) {
                bodies.emplace_back(orbitRadiusInput, radiusInput, colorInput, speedInput, nameInput);
                showAddPlanetPanel = false;
                nameInput[0] = '\0';
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !
            CheckCollisionPointRec(GetMousePosition(), {20, 75, 280, 400})) {
            showAddPlanetPanel = false;
        }
    }

    void drawListofPlanets() {
        for (size_t i = 1; i < bodies.size(); ++i) {
            if (GuiButton((Rectangle){screenWidth - 210, (float) (10 + i * 40), 200, 30},
                          TextFormat("Remove %s", bodies[i].name.c_str()))) {
                bodies.erase(bodies.begin() + i);
                break;
            }
        }
    }

    void draw() {

        update();
        drawPlanets();
        guiPanel();
        drawListofPlanets();

        DrawFPS(10, screenHeight - 30);
    }

private:
    std::vector<Body> bodies;


    Camera3D camera = {0};

    const int screenWidth = 800;
    const int screenHeight = 600;

    // GUI variables
    bool showAddPlanetPanel = false;
    char nameInput[64] = "";
    float orbitRadiusInput = 15.0f;
    float radiusInput = 0.5f;
    float speedInput = 0.5f;
    Color colorInput = RED;

    Texture2D circleTexture = LoadTexture("../Resources/sun.png");
};


#endif //SYSTEM_H
