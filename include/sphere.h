#ifndef SPHERE_H
#define SPHERE_H
#include "ray.h"
#include "hittable.h"
#include "stdbool.h"
#include "material.h"

typedef struct {
	Point center;
	double radius;
	Material *material;
} Sphere;

bool HitSphere(Ray ray, Sphere sphere, double minT, double maxT, HitInfo *hitInfo);

#endif
