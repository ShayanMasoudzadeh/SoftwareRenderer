#ifndef MATHLIB_H
#define MATHLIB_H

#include <iostream>

struct Vector2
{
	double x, y;
	Vector2(double x = 0, double y = 0);
	Vector2 operator+(const Vector2& v) const;
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator*(double scalar) const;
	double dot(const Vector2& v) const;
	double magnitude() const;
	Vector2 normalize() const;
};

struct Vector3
{
	double x, y, z;
	Vector3(double x = 0, double y = 0, double z = 0);
	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(double scalar) const;
	double dot(const Vector3& v) const;
	Vector3 cross(const Vector3& v) const;
	double magnitude() const;
	Vector3 normalize() const;
};

#endif