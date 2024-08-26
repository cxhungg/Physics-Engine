//
// Created by User on 8/4/2024.
//

#ifndef SPRING_LOOP_H
#define SPRING_LOOP_H



class spring_loop {

public:



    spring_loop() {
        mass = 1.0f;
        velocity = 0.0f;
        damping = 0.1f;
        displacement = 0.0f;
        initialVelocity = 0.0f;

        pause = true;
    }

    void drawControls() {

        GuiSliderBar((Rectangle){ 50, 20, 200, 20 }, "Mass", TextFormat("%.2f", mass), &mass, 0.1f, 10.0f);
        GuiSliderBar((Rectangle){ 50, 50, 200, 20 }, "Initial Velocity", TextFormat("%.2f", initialVelocity), &initialVelocity, -25.0f, 25.0f);
        GuiSliderBar((Rectangle){ 50, 80, 200, 20 }, "Damping", TextFormat("%.2f", damping), &damping, 0.0f, 1.0f);

    }
    void startPause() {
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
    void reset() {
        if (GuiButton((Rectangle){ 160, 110, 100, 30 }, "Reset")) {
            pause = true;
            velocity = 0.0f;
            displacement = 0.0f;
        }
    }
    void update() {

        if (!pause) {
            float acceleration = (-springConstant * displacement - damping * velocity) / mass;
            velocity += acceleration * GetFrameTime() * 28;
            displacement += velocity * GetFrameTime() * 28;
        }
    }
    void draw() {
        // Draw spring
        Vector2 start = { screenWidth / 2.0f, 0 };
        Vector2 end = { screenWidth / 2.0f, equilibriumY + displacement };
        DrawLineEx(start, end, 4, BLACK);

        // Draw mass
        //DrawCircle(screenWidth / 2, equilibriumY + displacement, 25, RED);



        DrawTexture(circleTexture,(screenWidth / 2)-circleRadius,equilibriumY + displacement-circleRadius,WHITE);

    }

    void displayValues() {
        // Display current values
        DrawText(TextFormat("Mass: %.2f", mass), 30, 180, 20, BLACK);
        DrawText(TextFormat("Velocity: %.2f", velocity), 30, 210, 20, BLACK);
        DrawText(TextFormat("Displacement: %.2f", displacement), 30, 240, 20, BLACK);

    }

    void render() {

        ClearBackground({145, 187, 255,255});

        drawControls();
        startPause();
        reset();
        update();
        draw();

        displayValues();
    }

private:

    float mass;
    float velocity;
    float damping;
    float displacement;
    float initialVelocity;

    bool pause;

    const int screenWidth = 800;
    const int screenHeight = 600;
    const float springConstant = 0.1f;
    const float equilibriumY = screenHeight / 2.0f;


    int circleRadius = 22;
    Texture2D circleTexture = LoadTexture("../Resources/smallblue.png");

};



#endif //SPRING_LOOP_H
