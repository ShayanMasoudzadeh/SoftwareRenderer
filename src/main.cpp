#include <SDL3/SDL.h>
#include <iostream>
#include "renderer.h"

// Window dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Canvas", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	Color* frameBuffer = getColors(SCREEN_WIDTH, SCREEN_HEIGHT);

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			Color currentPixel = frameBuffer[y * SCREEN_WIDTH + x];
			SDL_SetRenderDrawColor(renderer, currentPixel.r, currentPixel.g, currentPixel.b, SDL_ALPHA_OPAQUE);
			SDL_RenderPoint(renderer,x,y);
		}
	}

	delete[] frameBuffer;

	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
}
