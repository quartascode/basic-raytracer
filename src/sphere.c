#include "ray.h"
#include "hittable.h"
#include "vec3.h"
#include "sphere.h"
#include <math.h>
#include <stdbool.h>

bool HitSphere(Ray ray, Sphere sphere, double minT, double maxT, HitInfo *hitInfo){
	Vec3 oc = Vec3Subtract(sphere.center, ray.origin);
	double a = GetVec3LengthSquared(ray.direction);
	double h = DotProduct(ray.direction, oc);
	double c = GetVec3LengthSquared(oc) - sphere.radius * sphere.radius;
	double discriminant = h * h - a * c;

	if (discriminant < 0) {
		return false;
	}

	double sqrtDelta = sqrt(discriminant);

	double root = (h - sqrtDelta) / a;
	if (root <= minT || root >= maxT) {
		root = (h + sqrtDelta) / a;
		if (root <= minT || root >= maxT) {
			return false;
		}
	}

	hitInfo->t = root;
	hitInfo->hitPoint = GetRayPosAt(ray, hitInfo->t);
	Vec3 outwardNormal = Vec3Scale(Vec3Subtract(hitInfo->hitPoint, sphere.center), 1.0 / sphere.radius);
	SetFaceNormal(ray, outwardNormal, hitInfo);
	hitInfo->material = sphere.material;

	return true;
}
