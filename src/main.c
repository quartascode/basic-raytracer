#include <math.h>
#include <stdio.h>
#include "camera.h"
#include "material.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "world.h"
#include "raytracer.h"

int main() {
	// camera
	Camera camera;

	camera.aspectRatio = 16.0/9;
	camera.imageWidth = 400;
	camera.samplesPerPixel = 100;
	camera.rayBounceLimit = 10;

	camera.vFov = 90;
	camera.lookAt = (Vec3){0, 0, -2.0};
	int k = 1;
	camera.lookFrom = (Vec3){2*k, 3*k, 1*k};
	camera.vUp = (Vec3){0, 1, 0};

	// world
	Material metal = {
		.type = METAL,
		.albedo = (Color){0.8, 0.8, 0.8},
		.fuzz = 0.0
	};
	Material whiteMetal = {
		.type = METAL,
		.albedo = (Color){1.0, 1.0, 1.0},
		.fuzz = 0.5
	};
	Material grayLambertian = {
		.type = LAMBERTIAN,
		.albedo = (Color){0.3, 0.3, 0.3}
	};
	Material redLambertian = {
		.type = LAMBERTIAN,
		.albedo = (Color){0.7, 0.0, 0.0}
	};
	Material blueLambertian = {
		.type = LAMBERTIAN,
		.albedo = (Color){0.0, 0.3, 0.5}
	};
	Material Glass = {
		.type = DIELETRIC,
		.albedo = (Color){1.0, 1.0, 1.0},
		.refractionIndex = 1.5
	};
	Material insideGlass = {
		.type = DIELETRIC,
		.albedo = (Color){0.0, 0.5, 0.7},
		.refractionIndex = 1.0 / 1.5
	};

	Sphere spheres[6] = {
		{ .center = {0, -100.5, -2}, .radius = 100, .material = &grayLambertian },
		{ .center = {-1.0, 1, -4}, .radius = 1.5, .material = &metal },
		{ .center = {1.0, 0, -2}, .radius = 0.5, .material = &redLambertian },
		{ .center = {1.2, 1.25, -0.45}, .radius = .75, .material = &Glass },
	//	{ .center = {0.0, 0, -2}, .radius = 0.4, .material = &insideGlass },
		{ .center = {0.0, 0, -2.5}, .radius = 0.5, .material = &blueLambertian },
	};

	World world = {
		.spheres = spheres,
		.count = 6,
	};


	InitializeCamera(&camera);

	Render(world, &camera);

	return 0;
}
