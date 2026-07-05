#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "world.h"
#include "raytracer.h"
#include <math.h>
#include <stdio.h>

void InitializeCamera(Camera *cam) {
	cam->imageHeight = (int)(cam->imageWidth / cam->aspectRatio);

	cam->pixelSampleScale = 1.0 / cam->samplesPerPixel;

	cam->center = cam->lookFrom;

	double focalLength = GetVec3Length(Vec3Subtract(cam->lookFrom, cam->lookAt));
	double theta = DegreesToRadians(cam->vFov);
	double h = tan(theta / 2);

	double viewportHeight = 2.0 * h * focalLength;
	double viewportWidth = viewportHeight * (double)(cam->imageWidth)/cam->imageHeight;

	cam->w = Normalize(Vec3Subtract(cam->lookFrom, cam->lookAt));
	cam->u = Normalize(CrossProduct(cam->vUp, cam->w));
	cam->v = CrossProduct(cam->w, cam->u);

	Vec3 viewportU = Vec3Scale(cam->u, viewportWidth);
	Vec3 viewportV = Vec3Scale(Vec3Invert(cam->v), viewportHeight);

	// Pixels
	cam->pixelDeltaU = Vec3Divide(viewportU, CastVec3(cam->imageWidth));
	cam->pixelDeltaV = Vec3Divide(viewportV, CastVec3(cam->imageHeight));

	Vec3 viewportUpperLeft = Vec3Subtract(Vec3Subtract(cam->center, Vec3Scale(cam->w, focalLength)), Vec3Add(Vec3Scale(viewportU, 0.5), Vec3Scale(viewportV, 0.5)));
	cam->firstPixelPosition = Vec3Add(viewportUpperLeft, Vec3Scale(Vec3Add(cam->pixelDeltaV, cam->pixelDeltaU), 0.5));
}


Color RayColor(Ray ray, World world, int rayBounceLimit) {
	if (rayBounceLimit <= 0) {
		return (Color){0, 0, 0};
	}
	
	HitInfo hitInfo;

	if (WorldHit(ray, &hitInfo, 0.001, INFINITY, world)) {
		Ray scattered;
		Color attenuation;
		Color rayColor = (Vec3){1, 1, 1};

		Vec3 incomingLight = (Vec3){0, 0, 0};

		Ray shadowRay;

		switch (hitInfo.material->type) {
			case LAMBERTIAN:
				if (LambertianScatter(*hitInfo.material, hitInfo, &attenuation, &scattered)) {
					return Vec3Multiply(attenuation, RayColor(scattered, world, rayBounceLimit - 1));
				}
				break;
			case METAL:
				if (MetalScatter(*hitInfo.material, hitInfo, &attenuation, &scattered, ray)) {
					return Vec3Multiply(attenuation, RayColor(scattered, world, rayBounceLimit - 1));
				}
				break;
			case DIELETRIC:
				if (DieletricScatter(*hitInfo.material, hitInfo, &attenuation, &scattered, ray)) {
					return Vec3Multiply(attenuation, RayColor(scattered, world, rayBounceLimit - 1));
				}
				break;
			case LIGHT_SOURCE:
				Vec3 emittedLight = Vec3Scale(hitInfo.material->emissionColor, hitInfo.material->emissionStrength);
				incomingLight = Vec3Add(incomingLight, Vec3Multiply(emittedLight, rayColor));
				return incomingLight;
		}
	//	return (Color){0, 0, 0};
	}
	Vec3 unitDirection = Normalize(ray.direction);
	double a = 0.5 * (unitDirection.y + 1.0);
	return Vec3Add(Vec3Scale((Color){1.0, 1.0, 1.0}, 1.0 - a), Vec3Scale((Color){0.4, 0.7, 1.0}, a));
	//return (Color){0, 0, 0};
}

Vec3 SampleSquare() {
	return (Vec3){GetRandomNumber(0.0, 1.0) - 0.5, GetRandomNumber(0.0, 1.0) - 0.5, 0};
}

Ray GetRay(int i, int j, Camera *cam) {
	Vec3 offset = SampleSquare();
	Vec3 a = Vec3Scale(cam->pixelDeltaU, i + offset.x);
	Vec3 b = Vec3Scale(cam->pixelDeltaV, j + offset.y);
	Vec3 pixelSample = Vec3Add(Vec3Add(cam->firstPixelPosition, a), b);

	Ray ray;

	ray.origin = cam->center;
	ray.direction = Vec3Subtract(pixelSample, ray.origin);

	return ray;
}

void Render(World world, Camera *cam) {
	WritePPMHeader(cam->imageWidth, cam->imageHeight);
	for (int j = 0; j < cam->imageHeight; j++) {
		fprintf(stderr, "\rScanlines remaining: %d ", cam->imageHeight - j - 1);
		fflush(stderr);
		for (int i = 0; i < cam->imageWidth; i++) {
			Color pixelColor = (Color){0, 0, 0};
			for (int sample = 0; sample < cam->samplesPerPixel; sample++) {
				Ray ray = GetRay(i, j, cam);
				pixelColor = Vec3Add(RayColor(ray, world, cam->rayBounceLimit), pixelColor);
			}

			WriteColor(Vec3Scale(pixelColor, cam->pixelSampleScale));
		}
	}

	fprintf(stderr, "\nDone\n");
}
