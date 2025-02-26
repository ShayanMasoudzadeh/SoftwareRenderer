#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color {
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    Color();
};

#endif  // COLOR_H
