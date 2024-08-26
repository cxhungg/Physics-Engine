//
// Created by User on 8/9/2024.
//

#ifndef QUADTREE_H
#define QUADTREE_H

#include "raylib.h"
#include "particle.h"
#include <memory>
#include <cmath>
#include <vector>

class QuadTree {
public:

    QuadTree(Rectangle bounds, int capacity) : bounds(bounds), capacity(capacity) {}

    void insert(Particle* ball) {
        if (balls.size() < capacity) {
            balls.push_back(ball);
        } else if (!divided) {
            subdivide();
        }

        if (divided) {
            if (northeast->contains(ball->position)) northeast->insert(ball);
            else if (northwest->contains(ball->position)) northwest->insert(ball);
            else if (southeast->contains(ball->position)) southeast->insert(ball);
            else if (southwest->contains(ball->position)) southwest->insert(ball);
        }
    }

    void clear() {
        balls.clear();
        if (divided) {
            northeast.reset();
            northwest.reset();
            southeast.reset();
            southwest.reset();
            divided = false;
        }
    }

    std::vector<Particle*> query(Rectangle range) {
        std::vector<Particle*> found;
        if (!CheckCollisionRecs(bounds, range)) return found;

        for (Particle* ball : balls) {
            if (CheckCollisionPointRec(ball->position, range)) {
                found.push_back(ball);
            }
        }

        if (divided) {
            auto ne = northeast->query(range);
            auto nw = northwest->query(range);
            auto se = southeast->query(range);
            auto sw = southwest->query(range);
            found.insert(found.end(), ne.begin(), ne.end());
            found.insert(found.end(), nw.begin(), nw.end());
            found.insert(found.end(), se.begin(), se.end());
            found.insert(found.end(), sw.begin(), sw.end());
        }

        return found;
    }

    void draw() {
        DrawRectangleLinesEx(bounds, 1, GRAY);
        if (divided) {
            northeast->draw();
            northwest->draw();
            southeast->draw();
            southwest->draw();
        }
    }

private:
    Rectangle bounds;
    int capacity;
    std::vector<Particle*> balls;
    bool divided = false;
    std::unique_ptr<QuadTree> northeast;
    std::unique_ptr<QuadTree> northwest;
    std::unique_ptr<QuadTree> southeast;
    std::unique_ptr<QuadTree> southwest;

    void subdivide() {
        float x = bounds.x;
        float y = bounds.y;
        float w = bounds.width / 2;
        float h = bounds.height / 2;

        northeast = std::make_unique<QuadTree>(Rectangle{x + w, y, w, h}, capacity);
        northwest = std::make_unique<QuadTree>(Rectangle{x, y, w, h}, capacity);
        southeast = std::make_unique<QuadTree>(Rectangle{x + w, y + h, w, h}, capacity);
        southwest = std::make_unique<QuadTree>(Rectangle{x, y + h, w, h}, capacity);

        divided = true;
    }

    bool contains(Vector2 point) {

        return CheckCollisionPointRec(point, bounds);
    }
};

#endif //QUADTREE_H
