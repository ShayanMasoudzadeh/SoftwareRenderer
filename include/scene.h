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
    //Material features
    Color color; //Color of the material
    double specular; //Specular exponent of the material. -1: matte, 10: somewhat shiny, 500: shiny, 1000: very shiny 

    Sphere(Vector3 c = Vector3(), double r = 1.0, Color cl = Color(), double spec = -1.0) : center(c), radius(r), color(cl), specular(spec) {}
};

// Light base class
class Light {
public:
    double intensity;

    Light(double intensity = 0.0) : intensity(intensity) {}

    virtual ~Light() {}

    virtual std::string getType() const = 0;
};

// Ambient light class
class AmbientLight : public Light {
public:
    AmbientLight(double intensity = 0.0) : Light(intensity) {}

    std::string getType() const override {
        return "AmbientLight";
    }
};

// Point light class
class PointLight : public Light {
public:
    Vector3 position;

    PointLight(double intensity = 0.0, Vector3 pos = Vector3()) : Light(intensity), position(pos) {}

    std::string getType() const override {
        return "PointLight";
    }
};

// Directional Light class
class DirectionalLight : public Light {
public:
    Vector3 direction;

    DirectionalLight(double intensity = 0.0, Vector3 dir = Vector3()) : Light(intensity), direction(dir) {}

    std::string getType() const override {
        return "DirectionalLight";
    }
};

// Scene Class
class Scene {
public:
    Camera cam;
    std::vector<Sphere> spheres;
    std::vector<Light*> lights;

    Scene(Camera camera = Camera()) : cam(camera) {}

    /*~Scene() {
        // Clean up allocated memory
        for (Light* light : lights) {
            delete light;
        }
    }*/

    // Add a sphere to the scene
    void addSphere(const Sphere& sphere) {
        spheres.push_back(sphere);
    }

    // Add a light to the scene
    void addLight(Light* light) {
        lights.push_back(light);
    }
};

#endif