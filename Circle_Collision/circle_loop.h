//
// Created by User on 8/26/2024.
//

#ifndef CIRCLE_LOOP_H
#define CIRCLE_LOOP_H

#include "circle.h"
#include "raymath.h"

class circle_loop {
public:
    circle_loop() {
        createBalls();
    }

    void createBalls() {

        for (int i = 0; i < NUM_BALLS; i++) {
            balls.push_back({
                {static_cast<float>(GetRandomValue(BALL_RADIUS, SCREEN_WIDTH - BALL_RADIUS)),
                 static_cast<float>(GetRandomValue(BALL_RADIUS, SCREEN_HEIGHT - BALL_RADIUS))},
                {0, 0},
                {static_cast<unsigned char>(GetRandomValue(50, 255)),
                 static_cast<unsigned char>(GetRandomValue(50, 255)),
                 static_cast<unsigned char>(GetRandomValue(50, 255)),
                 255}
            });
        }
    }

    void UpdateBallPosition(Circle& ball) {


        ball.position.x += ball.velocity.x * GetFrameTime();
        ball.position.y += ball.velocity.y * GetFrameTime();

        // Constrain balls within walls
        ball.position.x = Clamp(ball.position.x, BALL_RADIUS, SCREEN_WIDTH - BALL_RADIUS);
        ball.position.y = Clamp(ball.position.y, BALL_RADIUS, SCREEN_HEIGHT - BALL_RADIUS);

        // Bounce off walls
        if (ball.position.x == BALL_RADIUS || ball.position.x == SCREEN_WIDTH - BALL_RADIUS) {
            ball.velocity.x *= -1;
        }
        if (ball.position.y == BALL_RADIUS || ball.position.y == SCREEN_HEIGHT - BALL_RADIUS) {
            ball.velocity.y *= -1;
        }

        // Apply friction
        ball.velocity = Vector2Scale(ball.velocity, 0.99f);

    }
    void ResolveCollision(Circle& b1, Circle& b2) {


        Vector2 delta = Vector2Subtract(b2.position, b1.position);
        float distance = Vector2Length(delta);

        if (distance < 2 * BALL_RADIUS) {
            Vector2 collisionNormal = Vector2Normalize(delta);

            // Separate balls immediately
            float overlap = 2 * BALL_RADIUS - distance;
            Vector2 separation = Vector2Scale(collisionNormal, overlap / 2);
            b1.position = Vector2Subtract(b1.position, separation);
            b2.position = Vector2Add(b2.position, separation);

            Vector2 relativeVelocity = Vector2Subtract(b2.velocity, b1.velocity);
            float velocityAlongNormal = Vector2DotProduct(relativeVelocity, collisionNormal);

            if (velocityAlongNormal > 0) return;

            float j = -(1 + ELASTICITY) * velocityAlongNormal;
            j /= 2;

            Vector2 impulse = Vector2Scale(collisionNormal, j);
            b1.velocity = Vector2Subtract(b1.velocity, impulse);
            b2.velocity = Vector2Add(b2.velocity, impulse);
        }
    }

    void mouseMechanics() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            for (int i = 0; i < NUM_BALLS; i++) {
                if (CheckCollisionPointCircle(mousePos, balls[i].position, BALL_RADIUS)) {
                    draggedBall = i;
                    break;
                }
            }
        } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            draggedBall = -1;
        }

        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();

            for (int i = 0; i < NUM_BALLS; i++) {
                if (CheckCollisionPointCircle(mousePos, balls[i].position, BALL_RADIUS)) {
                    draggedBall = i;
                    dragStart = mousePos;

                    break;
                }
            }
            DrawLineV(dragStart,mousePos,RED);
        } else if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON) && draggedBall != -1) {
            Vector2 dragEnd = GetMousePosition();
            Vector2 dragVector = Vector2Subtract(dragStart, dragEnd);
            balls[draggedBall].velocity = Vector2Scale(dragVector, 3.f);
            draggedBall = -1;
        }

        if (draggedBall != -1) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                // Constrain dragged ball within window
                mousePos.x = Clamp(mousePos.x, BALL_RADIUS, SCREEN_WIDTH - BALL_RADIUS);
                mousePos.y = Clamp(mousePos.y, BALL_RADIUS, SCREEN_HEIGHT - BALL_RADIUS);
                balls[draggedBall].position = mousePos;
                balls[draggedBall].velocity = {0, 0};
            }
        }
    }

    void render() {
        // Update ball positions
        for (auto& ball : balls) {
            UpdateBallPosition(ball);
        }

        // Check for collisions
        for (size_t i = 0; i < balls.size(); i++) {
            for (size_t j = i + 1; j < balls.size(); j++) {
                ResolveCollision(balls[i], balls[j]);
            }
        }

        mouseMechanics();



        ClearBackground({44, 44, 127, 255});

        for (const auto& ball : balls) {
            Vector2 texturePos = ball.position;
            texturePos.x -= BALL_RADIUS;
            texturePos.y -= BALL_RADIUS;

            //DrawCircleV(ball.position, BALL_RADIUS, ball.color);
            DrawTextureV(circleTexture,texturePos,WHITE);
        }
    }


private:

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int NUM_BALLS = 7;
    const float BALL_RADIUS = 22.0f;
    const float ELASTICITY = 0.85f;


    std::vector<Circle> balls;


    int draggedBall = -1;
    Vector2 dragStart = {0, 0};

    Texture2D circleTexture = LoadTexture("../Resources/smallblue.png");
};



#endif //CIRCLE_LOOP_H
