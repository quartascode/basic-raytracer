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
	camera.imageWidth = 1920;
	camera.samplesPerPixel = 1000;
	camera.rayBounceLimit = 50;

	camera.vFov = 20;
	camera.lookAt = (Vec3){0, 0, -2.0};
	// 0 4 10
	camera.lookFrom = (Vec3){0, 4, 10};
	camera.vUp = (Vec3){0, 1, 0};

	// world
	Material glass = {
		.type = DIELETRIC,
		.albedo = (Color){0.99, 0.99, 0.99},
		.refractionIndex = 1.5
	};
	Material insideGlass = {
		.type = DIELETRIC,
		.albedo = (Color){1.0, 1.0, 1.0},
		.refractionIndex = 1.0 / 1.5
	};
	Material water = {
		.type = DIELETRIC,
		.albedo = (Color){1.0, 1.0, 1.0},
		.refractionIndex = 1.33
	};
	Material mirror = {
		.type = METAL,
		.albedo = (Color){1.0, 1.0, 1.0},
		.fuzz = 0.0
	};
	Material metal = {
		.type = METAL,
		.albedo = (Color){0.4, 0.4, 0.4},
		.fuzz = 0.5
	};
	Material planet = {
		.type = LAMBERTIAN,
		.albedo = (Color){0.2, 0.4, 0.8}
	};
	Material sphereOne = {
		.type = LAMBERTIAN,
		.albedo = (Color){0.7, 0.7, 0.0}
	};
	Material sphereTwo = {
		.type = LAMBERTIAN,
		.albedo = (Color){0.5, 0.0, 0.5}
	};

	Sphere spheres[6] = {
		{ .center = {0, -100.5, -2}, .radius = 100, .material = &planet },
		{ .center = {1.0, 0, -2}, .radius = 0.5, .material = &sphereOne },
		{ .center = {0.0, 0, -2}, .radius = 0.5, .material = &metal },
		{ .center = {-1.0, 0, -2}, .radius = 0.5, .material = &sphereTwo },
		{ .center = {0.5, 0.0, -1.0}, .radius = 0.5, .material = &glass },
		{ .center = {0.5, 0.0, -1.0}, .radius = 0.4, .material = &insideGlass },
	};

	World world = {
		.spheres = spheres,
		.count = 6,
	};


	InitializeCamera(&camera);

	Render(world, &camera);

	return 0;
}
