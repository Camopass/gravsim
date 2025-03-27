#pragma once
#include "raylib.h"
#include "body.h"


Vector2 gravitationalAcceleration(Body* b1, Body* b2);

Vector2 vec2Dist(Vector2 a, Vector2 b);

float vec2Length(Vector2 v);

void vec2Normalize(Vector2 *v);
