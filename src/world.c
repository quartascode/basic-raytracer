#include "world.h"
#include <stdbool.h>
#include "hittable.h"
#include "ray.h"
#include "sphere.h"

bool WorldHit(Ray ray, HitInfo *hitInfo, double minT, double maxT, World world) {
	HitInfo tempInfo;
	bool hitAnything = false;
	double closestSoFar = maxT;

	for (int i = 0; i < world.count; i++) {
		if (HitSphere(ray, world.spheres[i], minT, closestSoFar, &tempInfo)) {
			hitAnything = true;
			closestSoFar = tempInfo.t;
			*hitInfo = tempInfo;
		}
	}
	return hitAnything;
}
