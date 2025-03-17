#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Color.h"
#include "scene.h"
#include "mathlib.h"

Color TraceRay(Vector3 O, Vector3 D, double t_min, double t_max, std::vector<Sphere> spheres);

void IntersectRaySphere(Vector3 O, Vector3 D, Sphere sphere, double t[2]);

#endif