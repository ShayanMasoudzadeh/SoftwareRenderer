#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SDL3/SDL.h>
#include <iostream>
#include "color.h"

class WindowManager {
public:
    WindowManager(int width, int height);
    ~WindowManager();

    bool Init(); // Initializes SDL, creates window and renderer
    void PutPixel(int x, int y, Color color); // Draw a pixel at (x, y)
    void Clear(Color color); // Clears screen with a color
    void Present(); // Updates the screen
    bool IsRunning(); // Check if the window is open
    void HandleEvents(); // Handles window events

private:
    int screenWidth, screenHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
};

#endif