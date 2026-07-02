#include "raytracer.h"
#include "vec3.h"
#include "hittable.h"
#include <math.h>
#include <stdbool.h>
#include "material.h"

bool LambertianScatter(Material lambertian, HitInfo hitInfo, Color *attenuation, Ray *scattered) {
	Vec3 scatterDirection = Vec3Add(hitInfo.normal, RandomUnitVector());

	if (Vec3NearZero(scatterDirection)) {
		scatterDirection = hitInfo.normal;
	}

	*scattered = (Ray){ .origin = hitInfo.hitPoint, .direction = scatterDirection };
	*attenuation = lambertian.albedo;

	return true;
}


bool MetalScatter(Material metal, HitInfo hitInfo, Color *attenuation, Ray *scattered, Ray rayIn) {
	Vec3 reflected = Reflect(rayIn.direction, hitInfo.normal);
	reflected = Vec3Add(Normalize(reflected), Vec3Scale(RandomUnitVector(), metal.fuzz));

	*scattered = (Ray){ .origin = hitInfo.hitPoint, .direction = reflected };
	*attenuation = metal.albedo;

	return DotProduct(scattered->direction, hitInfo.normal) > 0;
}

double Reflactence(double cos, double refractionIndex) {
	double r0 = (1 - refractionIndex) / (1 + refractionIndex);
	r0 *= r0;
	return r0 + (1-r0) * pow(1 - cos, 5);
}

bool DieletricScatter(Material dieletric, HitInfo hitInfo, Color *attenuation, Ray *scattered, Ray rayIn) {
	//*attenuation = (Color){1.0, 1.0, 1.0};
	*attenuation = dieletric.albedo;
	double ri = hitInfo.frontFace ? (1.0 / dieletric.refractionIndex) : dieletric.refractionIndex;

	Vec3 unitDirection = Normalize(rayIn.direction);

	double cosTheta = fmin(DotProduct(Vec3Scale(unitDirection, -1), hitInfo.normal), 1.0);
	double sinTheta = sqrt(1 - cosTheta * cosTheta);

	bool cannotRefract = ri * sinTheta > 1.0;
	Vec3 direction;

	if (cannotRefract || Reflactence(cosTheta, ri) > GetRandomNumber(0.0, 1.0)) {
		direction = Reflect(unitDirection, hitInfo.normal);
	} else {
		direction = Refract(unitDirection, hitInfo.normal, ri);
	}
	
	*scattered = (Ray){ .origin = hitInfo.hitPoint, .direction = direction };
	return true;
}
