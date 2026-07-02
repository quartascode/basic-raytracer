#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "world.h"

typedef struct {
	double aspectRatio;
	int imageWidth;
	int imageHeight;
	Point center;
	Point firstPixelPosition;
	Vec3 pixelDeltaU;
	Vec3 pixelDeltaV;
	int samplesPerPixel;
	double pixelSampleScale;
	int rayBounceLimit;
	double vFov;
	Point lookFrom;
	Point lookAt;
	Vec3 vUp;
	Vec3 u, v, w;
} Camera;

void InitializeCamera(Camera *cam);

Color RayColor(Ray ray, World world, int rayBounceLimit);

void Render(World world, Camera *cam);

#endif
