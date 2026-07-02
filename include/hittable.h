#ifndef HITTABLE_H
#define HITTABLE_H
#include "ray.h"
#include <stdbool.h>

typedef struct Material Material;

typedef struct {
	Point hitPoint;
	Vec3 normal;
	double t;
	bool frontFace;
	Material *material;
} HitInfo;

void SetFaceNormal(Ray ray, Vec3 outwardNormal, HitInfo *hitInfo);

#endif
