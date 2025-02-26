#include "color.h"

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : r(red), g(green), b(blue), a(alpha) {}
Color::Color(){
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}
