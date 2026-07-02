#ifndef WORLD_H
#define WORLD_H
#include "sphere.h"

typedef struct {
	Sphere *spheres;
	int count;
} World;

bool WorldHit(Ray ray, HitInfo *hitInfo, double minT, double maxT, World world);

#endif
