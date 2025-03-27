#include <raylib.h>
#include "body.h"

#include <math.h>
#include <stdio.h>

#include "mathutil.h"

#define speed 1e-15

// run verlet integration algorithm to update positions and velocities
void update_body(Body* body, Vector2 newAcceleration, float deltaTime) {
    struct Vector2 new_position;
    new_position.x = body->position.x + body->velocity.x * deltaTime + (0.5f * body->acceleration.x * deltaTime * deltaTime);
    new_position.y = body->position.y + body->velocity.y * deltaTime + (0.5f * body->acceleration.y * deltaTime * deltaTime);
    body->position = new_position;
    struct Vector2 new_velocity;
    new_velocity.x = body->velocity.x + 0.5f * (body->acceleration.x + newAcceleration.x) * deltaTime;
    new_velocity.y = body->velocity.y + 0.5f * (body->acceleration.y + newAcceleration.y) * deltaTime;
    body->velocity = new_velocity;
    body->acceleration = newAcceleration;
}

// Handle all movement
void update_bodies(Body* bodies[], int num, float deltaTime) {
    // Calculate Gravitational forces
    Vector2 accelerations[num];
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (i == j) {continue;}
            Vector2 acc = gravitationalAcceleration(bodies[i], bodies[j]);
            accelerations[i] = acc;
        }
    }
    // apply all forces
    for (int i = 0; i < num; i++) {
        update_body(bodies[i], accelerations[i], deltaTime);
    }
}

// Determine if one circular body intersects another
bool isColliding(Body* a, Body* b) {
    float dist = vec2Length(vec2Dist(a->position, b->position));
    if (dist < (a->radius + b->radius)) {
        return true;
    }
    return false;
}