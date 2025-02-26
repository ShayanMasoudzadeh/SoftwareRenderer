#include <iostream>
#include "renderer.h"

Color* getColors(int width, int height) {
	int size = width * height;
	Color* buffer = new Color[size];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            buffer[y * width + x].r = (x * 255) / width;
            buffer[y * width + x].g = (y * 255) / height;
            buffer[y * width + x].b = 128;
            buffer[y * width + x].a = 255;
        }
    }
    return buffer;
}