/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/
#include <stdio.h>
#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "body.h"
#include "camera.h"

int main () {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "gravsim");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Body Initialization
	struct Body b1;
	b1.position.x = 300;
	b1.position.y = 0;
	b1.velocity.y = 6;
	b1.mass = 7.3e13;
	b1.radius = 75;
	struct Body b2;
	b2.position.x = 0;
	b2.position.y = 200;
	b2.velocity.x = -12;
	b2.mass = 4e13;
	b2.radius = 50;
	struct Body b3;
	b3.position.x = 0;
	b3.position.y = 0;
	b3.mass = 25e13;
	b3.radius = 100;

	struct Camera camera;
	camera.position.x = -GetScreenWidth() / 2;
	camera.position.y = - GetScreenHeight() / 2;

	struct Body* bodies[] = {&b1, &b2, &b3};
	
	// game loop
	while (!WindowShouldClose()) {	// run the loop untill the user presses ESCAPE or presses the Close button on the window 

		// physics calulations

		int num = sizeof(bodies) / sizeof(bodies[0]);
		update_bodies(bodies, num, GetFrameTime());


		// drawing
		BeginDrawing();
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);

		
		for (int i = 0; i < (num); i++) {
			DrawCircle(bodies[i]->position.x - camera.position.x, bodies[i]->position.y - camera.position.y, bodies[i]->radius, BLACK);
		}
		DrawText(TextFormat("FPS: %d    deltaTime: %f", GetFPS(), GetFrameTime()), 0, 0, 13, RED);
		
		DrawText(TextFormat("B1 Data: Position: (%f, %f)    Velocity: (%f, %f)    Acceleration: (%f, %f)", b1.position.x, b1.position.y, b1.velocity.x, b1.position.y, b1.acceleration.x, b1.acceleration.y), 0, 15, 13, RED);
		DrawText(TextFormat("B2 Data: Position: (%f, %f)    Velocity: (%f, %f)    Acceleration: (%f, %f)", b2.position.x, b2.position.y, b2.velocity.x, b2.position.y, b2.acceleration.x, b2.acceleration.y), 0, 30, 13, RED);
		DrawText(TextFormat("B3 Data: Position: (%f, %f)    Velocity: (%f, %f)    Acceleration: (%f, %f)", b3.position.x, b3.position.y, b3.velocity.x, b3.position.y, b3.acceleration.x, b3.acceleration.y), 0, 45, 13, RED);
		
		EndDrawing();
	}

	// cleanup

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
