#ifndef VEC3_H
#define VEC3_H

#include <stdbool.h>

typedef struct {
	double x;
	double y;
	double z;
} Vec3;

typedef Vec3 Point;
typedef Vec3 Color;

double DotProduct(Vec3 vec1, Vec3 vec2);

Vec3 Normalize(Vec3 vec);

Vec3 Vec3Add(Vec3 u, Vec3 v);

Vec3 Vec3Subtract(Vec3 u, Vec3 v);

Vec3 Vec3Multiply(Vec3 u, Vec3 v);

Vec3 Vec3Divide(Vec3 u, Vec3 v);

Vec3 CastVec3(double a);

Vec3 Vec3Scale(Vec3 v, double s);

Vec3 ToVec3(double a);

double GetVec3Length(Vec3 v);

double GetVec3LengthSquared(Vec3 v);

Vec3 Vec3Invert(Vec3 v);

Vec3 Vec3Random(double min, double max);

Vec3 RandomUnitVector();

Vec3 RandomOnHemisphere(Vec3 normal);

bool Vec3NearZero(Vec3 v);

Vec3 Reflect(Vec3 v, Vec3 n);

Vec3 Refract(Vec3 uv, Vec3 n, double etaRatio);

Vec3 CrossProduct(Vec3 u, Vec3 v);

#endif
