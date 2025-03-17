#ifndef SCENE_H
#define SCENE_H

#include "mathlib.h"
#include "color.h"
#include <vector>

// Camera Class
class Camera {
public:
    Vector3 location;
    double height, width;
    double distance;

    Camera(Vector3 loc = Vector3(), double h = 1.0, double w = 1.0, double d = 1.0)
        : location(loc), height(h), width(w), distance(d) {
    }
};

// Sphere Class
class Sphere {
public:
    Vector3 center;
    double radius;
    Color color;

    Sphere(Vector3 c = Vector3(), double r = 1.0, Color cl = Color()) : center(c), radius(r), color(cl) {}
};

// Scene Class
class Scene {
public:
    Camera cam;
    std::vector<Sphere> spheres;

    Scene(Camera camera = Camera()) : cam(camera) {}

    // Add a sphere to the scene
    void addSphere(const Sphere& sphere) {
        spheres.push_back(sphere);
    }
};

#endif