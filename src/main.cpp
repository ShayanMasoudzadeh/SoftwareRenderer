#include <SDL3/SDL.h>
#include <iostream>
#include "renderer.h"
#include "WindowManager.h"

// Window dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {

	WindowManager canvas(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!canvas.Init()) return -1;

	Color* frameBuffer = getColors(SCREEN_WIDTH, SCREEN_HEIGHT);
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			Color currentPixel = frameBuffer[y * SCREEN_WIDTH + x];
			canvas.PutPixel(x, y, currentPixel);
		}
	}
	delete[] frameBuffer;

	canvas.Present();

}
