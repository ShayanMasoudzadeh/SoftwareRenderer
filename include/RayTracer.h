#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Color.h"
#include "scene.h"
#include "mathlib.h"

Color TraceRay(Vector3 O, Vector3 D, double t_min, double t_max, Scene scene);

void IntersectRaySphere(Vector3 O, Vector3 D, Sphere sphere, double t[2]);

double ComputeLighting(Vector3 P, Vector3 N, const Scene scene);

#endif