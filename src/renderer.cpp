#include <iostream>
#include "renderer.h"

Color* getColors(int width, int height) {
	int size = width * height;
	Color* buffer = new Color[size];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            buffer[y * width + x] = Color(
                (x * 255) / width,
                (y * 255) / height,
                128
            );
        }
    }
    return buffer;
}