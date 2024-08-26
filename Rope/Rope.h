//
// Created by User on 8/5/2024.
//

#ifndef ROPE_H
#define ROPE_H

#include "Point.h"
#include <vector>
#include <cmath>

#include "raymath.h"

class Rope {


private:

    const int screenWidth = 800;
    const int screenHeight = 600;
    const int numPoints = 20;
    const float segmentLength = 20.0f;
    const float gravity = 9.81f;
    const float damping = 0.99f;
    const float ropeThickness = 8.0f;

    const Color ropeColor = RED;

    std::vector<Point> points;

public:
    Rope(float startX, float startY) {
        for (int i = 0; i < numPoints; i++) {
            points.emplace_back(startX, startY + i * segmentLength, i == 0);
        }
    }

    void Update(float deltaTime) {
        // Apply velocity verlet integration
        for (auto& point : points) {
            if (!point.isFixed) {
                Vector2 temp = point.position;
                point.position = Vector2Add(
                    Vector2Add(
                        point.position,
                        Vector2Scale(Vector2Subtract(point.position, point.oldPosition), damping)
                    ),
                    Vector2Scale({0, gravity}, deltaTime * deltaTime)
                );
                point.oldPosition = temp;
            }
        }

        // Apply constraints
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < numPoints - 1; j++) {
                Point& p1 = points[j];
                Point& p2 = points[j + 1];

                float distance = Vector2Distance(p1.position, p2.position);
                float difference = segmentLength - distance;
                float percent = difference / distance / 2;
                Vector2 offset = Vector2Scale(Vector2Subtract(p2.position, p1.position), percent);

                if (!p1.isFixed)
                    p1.position = Vector2Subtract(p1.position, offset);
                if (!p2.isFixed)
                    p2.position = Vector2Add(p2.position, offset);
            }
        }
    }

    void Draw() {
        // Draw lines between points
        for (int i = 0; i < numPoints - 1; i++) {
            DrawLineEx(points[i].position, points[i + 1].position, ropeThickness, ropeColor);
        }

        // Draw circles at each point for rounded ends and joints
        for (const auto& point : points) {
            DrawCircleV(point.position, ropeThickness / 2, BLUE);
        }
    }

    void SetAnchor(Vector2 position) {
        points[0].position = position;
        points[0].oldPosition = position;
    }

    void render() {


        float deltaTime = GetFrameTime()*15;

        // Update rope anchor to mouse position when left mouse button is pressed
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            SetAnchor(GetMousePosition());
        }
        Update(deltaTime);

        Draw();
    }

};

#endif //ROPE_H
