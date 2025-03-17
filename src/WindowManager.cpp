#include "WindowManager.h"

// Constructor
WindowManager::WindowManager(int width, int height)
    : screenWidth(width), screenHeight(height), window(nullptr), renderer(nullptr), running(true) {
}

// Destructor
WindowManager::~WindowManager() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

// Initialize SDL, create window and renderer
bool WindowManager::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_CreateWindowAndRenderer("Canvas", screenWidth, screenHeight, 0, &window, &renderer);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// Puts a pixel at (x, y) with the given color
void WindowManager::PutPixel(int x, int y, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderPoint(renderer, x, y);
}

// Clears the screen with a given color
void WindowManager::Clear(Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

// Presents the rendered frame
void WindowManager::Present() {
    SDL_RenderPresent(renderer);
}

// Handles window events
void WindowManager::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
    }
}

// Checks if the application is still running
bool WindowManager::IsRunning() {
    return running;
}