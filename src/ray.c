#include "ray.h"
#include "vec3.h"

Point GetRayPosAt(Ray ray, double t) {
	return Vec3Add(ray.origin, Vec3Multiply((Vec3){t, t, t}, ray.direction));
}
