//
// Created by User on 27/7/2024.
//

#include "game.h"

Game::Game() : quadtree({0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, 4){


}

Particle Game::createBall(Vector2 position) {

    Particle ball(position);
    return ball;
}

void Game::addBalls(Vector2 position, int count) {



    for (int i = 0; i < count && balls.size() < MAX_BALLS; i++) {
        balls.push_back(createBall(position));
    }
}

void Game::clear() {
    balls.clear();
}

void Game::updateBalls(float deltaTime) {

    quadtree.clear(); //---

    for (auto& ball : balls) {
        ball.position.x += ball.velocity.x * deltaTime;
        ball.position.y += ball.velocity.y * deltaTime;

        if (ball.position.x < BALL_RADIUS || ball.position.x > SCREEN_WIDTH - BALL_RADIUS) {
            ball.velocity.x *= -1;
        }
        if (ball.position.y < BALL_RADIUS || ball.position.y > SCREEN_HEIGHT - BALL_RADIUS) {
            ball.velocity.y *= -1;
        }

        quadtree.insert(&ball); //---
    }

    for (auto& ball : balls) {
        Rectangle queryRect = {
            ball.position.x - BALL_RADIUS * 2,
            ball.position.y - BALL_RADIUS * 2,
            BALL_RADIUS * 4,
            BALL_RADIUS * 4
        };

        auto nearbyBalls = quadtree.query(queryRect); //---

        for (auto& other : nearbyBalls) {
            if (&ball != other) {
                float dx = other->position.x - ball.position.x;
                float dy = other->position.y - ball.position.y;
                float distSquared = dx * dx + dy * dy;

                if (distSquared < 4 * BALL_RADIUS * BALL_RADIUS) {
                    float dist = sqrt(distSquared);
                    float overlap = 2 * BALL_RADIUS - dist;

                    dx /= dist;
                    dy /= dist;

                    ball.position.x -= overlap * dx * 0.5f;
                    ball.position.y -= overlap * dy * 0.5f;
                    other->position.x += overlap * dx * 0.5f;
                    other->position.y += overlap * dy * 0.5f;

                    float nx = dy;
                    float ny = -dx;

                    float p = 2 * (ball.velocity.x * dx + ball.velocity.y * dy - other->velocity.x * dx - other->velocity.y * dy) / 2;

                    ball.velocity.x -= p * dx;
                    ball.velocity.y -= p * dy;
                    other->velocity.x += p * dx;
                    other->velocity.y += p * dy;
                }
            }
        }
    }

}

void Game::mouseInput() {

    // Handle mouse input
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePosition = GetMousePosition();
        addBalls(mousePosition, BALLS_PER_CLICK);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePosition = GetMousePosition();
        addBalls(mousePosition, BALLS_PER_FRAME_HOLD);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        clear();
    }
}

void Game::render() {


    float deltaTime = GetFrameTime()*65;

    mouseInput();

    updateBalls(deltaTime);

    ClearBackground({251, 255, 212,255});


    quadtree.draw();

    for (const auto& ball : balls) {
        DrawCircleV(ball.position, BALL_RADIUS, ball.color);
    }

    DrawFPS(10, 10);
    DrawText(TextFormat("Balls: %d", (int)balls.size()), 10, 30, 20, DARKGRAY);

}
