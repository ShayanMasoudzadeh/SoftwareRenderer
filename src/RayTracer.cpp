#include <iostream>
#include <limits>
#include "RayTracer.h"

//FIX LATER!!!
Color TraceRay(Vector3 O, Vector3 D, double t_min, double t_max, std::vector<Sphere> spheres) {
	double closest_t = std::numeric_limits<double>::infinity();
	Sphere* closest_sphere = nullptr;
	Color closest_color = Color(0, 0, 0);
	for (Sphere sphere : spheres) {

		double t[2];
		IntersectRaySphere(O, D, sphere, t);
		if ((t[0] > t_min && t[0] < t_max) && t[0] < closest_t) {
			closest_t = t[0];
			closest_sphere = &sphere;
			closest_color = sphere.color;
		}
		if ((t[1] > t_min && t[1] < t_max) && t[1] < closest_t) {
			closest_t = t[1];
			closest_sphere = &sphere;
			closest_color = sphere.color;
		}
	}
	if (closest_sphere == nullptr) {
		return Color(0,0,0);
	}
	return closest_color;
}

void IntersectRaySphere(Vector3 O, Vector3 D, Sphere sphere, double t[2]) {
	double r = sphere.radius;
	Vector3 CO = O - sphere.center;

	double a = D.dot(D);
	double b = 2 * CO.dot(D);
	double c = CO.dot(CO) - r * r;

	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		t[0] = std::numeric_limits<double>::infinity();
		t[1] = std::numeric_limits<double>::infinity();
		return;
	}

	t[0] = (-b + sqrt(discriminant)) / (2 * a);
	t[1] = (-b - sqrt(discriminant)) / (2 * a);
	return;
}