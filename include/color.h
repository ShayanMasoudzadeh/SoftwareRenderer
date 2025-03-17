#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color {
public:
    uint8_t r; //red channel
    uint8_t g; //green channel
    uint8_t b; //blue channel

    //constructors
    Color(uint8_t red, uint8_t green, uint8_t blue);
    Color();

    Color operator+(const Color& other) const;
    Color operator*(double scalar) const;
};

#endif  // COLOR_H
