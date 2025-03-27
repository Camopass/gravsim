#include "mathutil.h"

#include <math.h>

#define G 6.67e-11


Vector2 gravitationalAcceleration(Body* b1, Body* b2) {
    Vector2 dist = vec2Dist(b1->position, b2->position);
    double len = sqrt(dist.x * dist.x + dist.y * dist.y);
    vec2Normalize(&dist);
    Vector2 acc;
    acc.x = -G * (b2->mass * dist.x / (len * len));
    acc.y = -G * (b2->mass * dist.y / (len * len));
    return acc;
}

Vector2 vec2Dist(Vector2 a, Vector2 b) {
    Vector2 c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
}

float vec2Length(Vector2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

void vec2Normalize(Vector2* v) {
    float len = vec2Length(*v);
    v->x /= len; v->y /= len;
}