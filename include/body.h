#pragma once

#include "raylib.h"

typedef struct  {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    float mass;
    float radius;
} Body;

extern void update_body(Body* body, Vector2 newAcceleration, float deltaTime);

extern void update_bodies(Body* bodies[], int num, float deltaTime);