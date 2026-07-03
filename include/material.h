#ifndef MATERIAL_H
#define MATERIAL_H
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

typedef enum {
    LAMBERTIAN,
    METAL,
    DIELETRIC,
    LIGHT_SOURCE,
} MaterialType;

typedef struct Material{
    MaterialType type;

    Color albedo;
    double fuzz;
    double refractionIndex;
    Color emissionColor;
    double emissionStrength;
} Material;

bool LambertianScatter(Material lambertian, HitInfo hitInfo, Color *attenuation, Ray *scattered);

bool MetalScatter(Material metal, HitInfo hitInfo, Color *attenuation, Ray *scattered, Ray rayIn);

bool DieletricScatter(Material dieletric, HitInfo hitInfo, Color *attenuation, Ray *scattered, Ray rayIn);

#endif
