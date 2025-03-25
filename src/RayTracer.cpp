#include <iostream>
#include <limits>
#include "RayTracer.h"

Color TraceRay(Vector3 O, Vector3 D, double t_min, double t_max, Scene scene, int recursion_depth) {
	double closest_t = std::numeric_limits<double>::infinity();
	Sphere* closest_sphere = ClosestIntersection(O, D, t_min, t_max, scene, &closest_t);

	if (closest_sphere == nullptr) {
		return Color(0,0,0);
	}
	
	//compute local color
	Vector3 P = O + (D * closest_t);
	Vector3 N = (P - closest_sphere->center).normalize();
	Color local_color = closest_sphere->color * ComputeLighting(P, N, (D * -1), closest_sphere->specular, scene);

	//exit conditions
	double r = closest_sphere->reflectiveness;
	if (recursion_depth <= 0 || r <= 0) {
		return local_color;
	}

	//compute reflected color
	Vector3 R = ReflectRay(D * -1, N);
	Color reflected_color = TraceRay(P, R, 0.001, std::numeric_limits<double>::infinity(), scene, recursion_depth - 1);
	return local_color * (1 - r) + reflected_color * r;
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

double ComputeLighting(Vector3 P, Vector3 N, Vector3 V, double s, const Scene scene) {
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

			//check for shadow
			double shadow_t = 0.0;
			Sphere* shadow_sphere = ClosestIntersection(P, L, 0.001, std::numeric_limits<double>::infinity(), scene, &shadow_t);
			if (shadow_sphere != nullptr) {
				continue;
			}

			//Diffuse reflection
			double n_dot_l = N.dot(L);
			if (n_dot_l > 0) {
				i += light->intensity * (n_dot_l / (N.magnitude() * L.magnitude()));
			}

			//Specular reflection
			if (s >= 0) {
				Vector3 R = ReflectRay(L, N);
				double r_dot_v = R.dot(V);
				if (r_dot_v > 0) {
					i += light->intensity * pow(r_dot_v / (R.magnitude() * V.magnitude()), s);
					i = i * 1;
				}
			}
		}

	}
	return i;
}

Sphere* ClosestIntersection(Vector3 O, Vector3 D, double t_min, double t_max, const Scene& scene, double* add_closest_t) {

	*add_closest_t = std::numeric_limits<double>::infinity();
	Sphere* closest_sphere = nullptr;
	for (const Sphere& sphere : scene.spheres) {

		double t[2];
		IntersectRaySphere(O, D, sphere, t);
		if ((t[0] > t_min && t[0] < t_max) && t[0] < *add_closest_t) {
			*add_closest_t = t[0];
			closest_sphere = const_cast<Sphere*>(& sphere);
		}
		if ((t[1] > t_min && t[1] < t_max) && t[1] < *add_closest_t) {
			*add_closest_t = t[1];
			closest_sphere = const_cast<Sphere*>(&sphere);
		}
	}
	return closest_sphere;
}

Vector3 ReflectRay(Vector3 R, Vector3 N) {
	return ((N * 2) * N.dot(R)) - R;
}