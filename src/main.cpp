#include <SDL3/SDL.h>
#include <iostream>
#include <limits>
#include "renderer.h"
#include "WindowManager.h"
#include "scene.h"
#include "RayTracer.h"

// Window dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

Vector3 CanvasToViewport(int x, int y, Camera cam) {
	return Vector3(
		x * cam.width / SCREEN_WIDTH,
		y * cam.height / SCREEN_HEIGHT,
		cam.distance
	);
}

void PutPixel(int x, int y, Color color, WindowManager* canvas) {
	int Cx = int(SCREEN_WIDTH / 2 + x);
	int Cy = int(SCREEN_HEIGHT / 2 - y);
	canvas->PutPixel(Cx, Cy, color);
}

int main(int argc, char* argv[]) {

	//initiate SDL window and renderer
	WindowManager canvas(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!canvas.Init()) return -1;

	//initiate scene
	Scene scene = Scene(Camera());
	scene.addSphere(Sphere(Vector3(0, -1, 3), 1.0, Color(255, 0, 0)));
	scene.addSphere(Sphere(Vector3(2, 0, 4), 1.0, Color(0, 0, 255)));
	scene.addSphere(Sphere(Vector3(-1, 0, 4.5), 1.0, Color(0, 255, 0)));

	//main rendering loop
	for (int x = -SCREEN_WIDTH / 2; x < SCREEN_WIDTH / 2; x++) {
		for (int y = -SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT / 2; y++) {
			Vector3 D = CanvasToViewport(x, y, scene.cam);
			Color color = TraceRay(scene.cam.location, D, 1, std::numeric_limits<double>::infinity(), scene.spheres);
			PutPixel(x, y, color, &canvas);
		}
	}
	canvas.Present();
	SDL_Delay(5000);
}