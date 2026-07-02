#include "hittable.h"
#include "ray.h"
#include "vec3.h"

void SetFaceNormal(Ray ray, Vec3 outwardNormal, HitInfo *hitInfo) {
	// NOTE: parameter outwardNormal is assumed unit length
	hitInfo->frontFace = DotProduct(ray.direction, outwardNormal) < 0;
	hitInfo->normal = hitInfo->frontFace ? outwardNormal : Vec3Invert(outwardNormal);
}
