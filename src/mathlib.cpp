#include "mathlib.h"
#include <cmath>

//2D Vector Definition
Vector2::Vector2(double x, double y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& v) const {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const {
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(double scalar) const {
	return Vector2(x * scalar, y * scalar);
}

double Vector2::dot(const Vector2& v) const {
	return x * v.x + y * v.y;
}

double Vector2::magnitude() const {
	return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalize() const {
	double mag = magnitude();
	return (mag > 0) ? Vector2(x / mag, y / mag) : Vector2();
}

//3D Vector Definition
Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(const Vector3& v) const {
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const {
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(double scalar) const {
	return Vector3(x * scalar, y * scalar, z * scalar);
}

double Vector3::dot(const Vector3& v) const {
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3& v) const {
	return Vector3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}

double Vector3::magnitude() const {
	return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalize() const {
	double mag = magnitude();
	return Vector3(x / mag, y / mag, z / mag);
}
