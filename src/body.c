#include <raylib.h>
#include "body.h"
#include <math.h>
#include <stdio.h>

#define G 6.67e-11
#define speed 1e-15

// run verlet integration algorithm to update positions and velocities
void update_body(struct Body* body, Vector2 newAcceleration, float deltaTime) {
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

// calculate forces between bodies, then update them
void update_bodies(struct Body* bodies[], int num, float deltaTime) {
    Vector2 accelerations[num];
    for (int i = 0; i < num; i++) {
        Vector2 total_forces;
        total_forces.x, total_forces.y = 0;
        for (int j = 0; j < num; j++) {
            if (i == j) {continue;}
            struct Vector2 dist;
            dist.x = bodies[j]->position.x - bodies[i]->position.x;
            dist.y = bodies[j]->position.y - bodies[i]->position.y;
            double len = sqrt(dist.x * dist.x + dist.y * dist.y);
            struct Vector2 dist_normalized;
            dist_normalized.x = dist.x / len;
            dist_normalized.y = dist.y / len;
            struct Vector2 acc_comp;
            acc_comp.x = G * (bodies[j]->mass * dist_normalized.x / (len * len));
            acc_comp.y = G * (bodies[j]->mass * dist_normalized.y / (len * len));
            total_forces.x = total_forces.x + acc_comp.x;
            total_forces.y = total_forces.y + acc_comp.y;
        }
        accelerations[i] = total_forces;
    }
    for (int i = 0; i < num; i++) {
        update_body(bodies[i], accelerations[i], deltaTime);
    }
}