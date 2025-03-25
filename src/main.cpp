#include <SDL3/SDL.h>
#include <iostream>
#include <limits>
#include <fstream>
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

	//create and prepare ppm file canvas
	std::ofstream canvas("output/render.ppm");
	canvas << "P3\n" << SCREEN_WIDTH << ' ' << SCREEN_HEIGHT << "\n255\n";

	//initiate scene
	Scene scene = Scene(Camera(Vector3(0,0,0),1,1,1));
	scene.addSphere(Sphere(Vector3(0, -1, 3), 1.0, Color(255, 0, 0), 500, 0.2));
	scene.addSphere(Sphere(Vector3(2, 0, 4), 1.0, Color(0, 0, 255), 500, 0.3));
	scene.addSphere(Sphere(Vector3(-2, 0, 4), 1.0, Color(0, 255, 0), 1000, 0.5));
	scene.addSphere(Sphere(Vector3(0, -5001, 0), 5000, Color(255, 255, 0), 10, 0.0));
	scene.addLight(new PointLight(0.6, Vector3(2, 2, 1)));
	scene.addLight(new DirectionalLight(0.2, Vector3(1, 4, 4)));
	scene.addLight(new AmbientLight(0.2));

	//main rendering loop
	for (int y = (SCREEN_HEIGHT / 2) - 1; y >= -SCREEN_HEIGHT / 2; y--) {
		for (int x = -SCREEN_WIDTH / 2; x < SCREEN_WIDTH / 2; x++) {
			Vector3 D = CanvasToViewport(x, y, scene.cam);
			Color color = TraceRay(scene.cam.location, D, 1, std::numeric_limits<double>::infinity(), scene, 3);
			canvas << static_cast<int>(color.r) << ' ' << static_cast<int>(color.g) << ' ' << static_cast<int>(color.b) << '\n';
		}
	}
}