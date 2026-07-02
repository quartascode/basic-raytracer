#include "vec3.h"
#include "raytracer.h"
#include <math.h>
#include <stdio.h>

double LinearToGammaSpace(double linearComponent) {
	if (linearComponent > 0) {
		return sqrt(linearComponent);
	}
	return 0;
}

void WriteColor(Color pixelColor) {
	double r = pixelColor.x;
	double g = pixelColor.y;
	double b = pixelColor.z;

	r = LinearToGammaSpace(r);
	g = LinearToGammaSpace(g);
	b = LinearToGammaSpace(b);

	int rbyte = (int)(256 * Clamp(r, 0.000, 0.999));
	int gbyte = (int)(256 * Clamp(g, 0.000, 0.999));
	int bbyte = (int)(256 * Clamp(b, 0.000, 0.999));

	printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

void WritePPMHeader(const int width, const int height) {
	printf("P3\n%d %d\n255\n", width, height);
}
