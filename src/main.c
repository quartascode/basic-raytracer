#include "camera.h"
#include "material.h"
#include "vec3.h"
#include "sphere.h"
#include "hittable.h"
#include "world.h"

int main() {
	// camera
	Camera camera;

	camera.aspectRatio = 16.0/9;
	camera.imageWidth = 1920;
	camera.samplesPerPixel = 5000;
	camera.rayBounceLimit = 100;

	camera.vFov = 30;
	camera.lookAt = (Vec3){0, 0, -2.0};
	// 0 4 10
	camera.lookFrom = (Vec3){3.0, 2, 5.0};
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
		.albedo = (Color){0.75, 0.75, 0.2},
		.fuzz = 0.5
	};
	Material planet = {
		.type = LAMBERTIAN,
		.albedo = (Color){0.8, 0.8, 0.8}
	};
	Material sphereOne = {
		.type = LAMBERTIAN,
		.albedo = (Color){0.9, 0.05, 0.05}
	};
	Material sphereTwo = {
		.type = LAMBERTIAN,
		.albedo = (Color){0.0, 0.9, 0.5}
	};
	Material sphereThree = {
		.type = LIGHT_SOURCE,
		.emissionColor = (Color){1, 1, 1},
		.emissionStrength = 5,
		.albedo = (Color){0.8, 0.8, 0.8}
	};

	Sphere spheres[4] = {
		{ .center = {50.0, 30, -50}, .radius = 45.0, .material = &sphereThree },
		{ .center = {1.2, 0, -1.5}, .radius = 0.5, .material = &sphereOne },
		{ .center = {-1.2, 0, -1.5}, .radius = 0.5, .material = &sphereTwo },
		{ .center = {0, -100.5, -2}, .radius = 100, .material = &planet },
	};

	World world = {
		.spheres = spheres,
		.count = sizeof(spheres) / sizeof(spheres[0]),
		.lightSorcePos = (Point){50, 30, -50},
	};


	InitializeCamera(&camera);

	Render(world, &camera);

	return 0;
}
