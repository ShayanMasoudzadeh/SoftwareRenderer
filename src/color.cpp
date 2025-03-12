#include "color.h"
#include <algorithm>

Color::Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}
Color::Color(){
	r = 0;
	g = 0;
	b = 0;
}

Color Color::operator+(const Color& other) const {
	return Color(
		std::min(255, std::max(0, r + other.r)),
		std::min(255, std::max(0, g + other.g)),
		std::min(255, std::max(0, b + other.b))
	);
}
