#include "vec3.h"
#include <stdbool.h>
#include "raytracer.h"
#include <math.h>
#include <stdlib.h>

double DotProduct(Vec3 vec1, Vec3 vec2) {
	return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}

Vec3 CrossProduct(Vec3 u, Vec3 v) {
	double x = u.y * v.z - u.z * v.y;
	double y = u.z * v.x - u.x * v.z;
	double z = u.x * v.y - u.y * v.x;
	return (Vec3){x, y, z};
}

Vec3 Normalize(Vec3 vec) {
	double magnitude = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (Vec3){vec.x / magnitude, vec.y / magnitude, vec.z / magnitude};
}

Vec3 Vec3Add(Vec3 u, Vec3 v) {
	return (Vec3){u.x + v.x, u.y + v.y, u.z + v.z};
}

Vec3 Vec3Subtract(Vec3 u, Vec3 v) {
	return (Vec3){u.x - v.x, u.y - v.y, u.z - v.z};
}

Vec3 Vec3Multiply(Vec3 u, Vec3 v) {
	return (Vec3){u.x * v.x, u.y * v.y, u.z * v.z};
}

Vec3 Vec3Divide(Vec3 u, Vec3 v) {
	return (Vec3){u.x / v.x, u.y / v.y, u.z / v.z};
}

Vec3 CastVec3(double a) {
	return (Vec3){a, a, a};
}

Vec3 Vec3Scale(Vec3 v, double s) {
	return (Vec3){v.x * s, v.y * s, v.z * s};
}

Vec3 ToVec3(double a) {
	return (Vec3){a, a, a};
}

double GetVec3Length(Vec3 v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double GetVec3LengthSquared(Vec3 v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

Vec3 Vec3Invert(Vec3 v) {
	return (Vec3){-v.x, -v.y, -v.z};
}

Vec3 Vec3Random(double min, double max) {
	return (Vec3){GetRandomNumber(min, max), GetRandomNumber(min, max), GetRandomNumber(min, max)};
}

Vec3 RandomUnitVector() {
	while (1 == 1) {
		Vec3 v = Vec3Random(-1.0, 1.0);
		double lengthSquared = GetVec3LengthSquared(v);
		if (pow(10, -160) < lengthSquared && lengthSquared <= 1) {
			return Vec3Scale(v, 1 / sqrt(lengthSquared));
		}
	}
}

Vec3 RandomOnHemisphere(Vec3 normal) {
	Vec3 onUnitSphere = RandomUnitVector();
	if (DotProduct(onUnitSphere, normal) > 0) {
		return onUnitSphere;
	}
	return Vec3Invert(onUnitSphere);
}

bool Vec3NearZero(Vec3 v) {
	double s = 1e-8;
	return (fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s);
}

Vec3 Reflect(Vec3 v, Vec3 n) {
	return Vec3Subtract(v, Vec3Scale(n, DotProduct(v, n)*2));
}

Vec3 Refract(Vec3 uv, Vec3 n, double etaRatio) {
	double cosTheta = fmin(DotProduct(Vec3Scale(uv, -1), n), 1.0);
	Vec3 rayOutPerpendicular = Vec3Scale(Vec3Add(uv, Vec3Scale(n, cosTheta)), etaRatio);
	Vec3 rayOutParallel = Vec3Scale(n, -sqrt(fabs(1 - GetVec3LengthSquared(rayOutPerpendicular))));
	return Vec3Add(rayOutPerpendicular, rayOutParallel);
}
