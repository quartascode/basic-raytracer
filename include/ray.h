#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
	Point origin;
	Vec3 direction;
} Ray;

Point GetRayPosAt(Ray ray, double t);

#endif
