#include <iostream>
#include <limits>
#include "RayTracer.h"

//FIX LATER!!!
Color TraceRay(Vector3 O, Vector3 D, double t_min, double t_max, Scene scene) {
	double closest_t = std::numeric_limits<double>::infinity();
	Sphere closest_sphere = Sphere(Vector3(), 0.0, Color());
	for (const Sphere sphere : scene.spheres) {

		double t[2];
		IntersectRaySphere(O, D, sphere, t);
		if ((t[0] > t_min && t[0] < t_max) && t[0] < closest_t) {
			closest_t = t[0];
			closest_sphere = sphere;
		}
		if ((t[1] > t_min && t[1] < t_max) && t[1] < closest_t) {
			closest_t = t[1];
			closest_sphere = sphere;
		}
	}
	if (closest_sphere.radius == 0.0) {
		return Color(0,0,0);
	}
	
	Vector3 P = O + (D * closest_t);
	Vector3 N = (P - closest_sphere.center).normalize();
	return closest_sphere.color * ComputeLighting(P, N, scene);
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

double ComputeLighting(Vector3 P, Vector3 N, const Scene scene) {
	double i = 0.0;
	for (const auto& light : scene.lights) {
		if (auto* ambLight = dynamic_cast<AmbientLight*>(light)) {
			i += ambLight->intensity;
		}
		else {
			Vector3 L = Vector3();
			if (auto* pntLight = dynamic_cast<PointLight*>(light)) {
				L = pntLight->position - P;
			}
			else if (auto* dirLight = dynamic_cast<DirectionalLight*>(light)) {
				L = dirLight->direction;
			}
			double n_dot_l = N.dot(L);
			if (n_dot_l > 0) {
				i += light->intensity * (n_dot_l / (N.magnitude() * L.magnitude()));
			}
		}

	}
	return i;
}