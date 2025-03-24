#pragma once

#include "raylib.h"

struct Body {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    float mass;
    float radius;
};

extern void update_body(struct Body* body, Vector2 newAcceleration, float deltaTime);

extern void update_bodies(struct Body* bodies[], int num, float deltaTime);