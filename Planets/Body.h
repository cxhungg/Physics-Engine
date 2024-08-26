//
// Created by User on 8/5/2024.
//

#ifndef BODY_H
#define BODY_H

#include "raylib.h"
#include <vector>
#include <cmath>
#include <string>

class Body {
public:
    Vector3 position;
    float radius;
    Color color;
    float orbitRadius;
    float orbitSpeed;
    float angle;
    std::string name;

    Body(float orbitR, float r, Color c, float speed, const std::string& n)
        : orbitRadius(orbitR), radius(r), color(c), orbitSpeed(speed), angle(0), name(n) {
        UpdatePosition();
    }

    void Update(float deltaTime) {
        angle += orbitSpeed * deltaTime;
        if (angle > 2 * PI) angle -= 2 * PI;
        UpdatePosition();
    }

    void UpdatePosition() {
        position.x = orbitRadius * cos(angle);
        position.z = orbitRadius * sin(angle);
        position.y = 0;
    }

    void Draw() {
        DrawSphere(position, radius, color);
    }

    void DrawOrbit() {
        if (orbitRadius > 0) {
            DrawCircle3D({0, 0, 0}, orbitRadius, {1, 0, 0}, 90, Fade(color, 0.5f));
        }
    }
};

#endif //BODY_H
