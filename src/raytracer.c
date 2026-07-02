#include "raytracer.h"
#include <stdlib.h>

double DegreesToRadians(double deg) {
	return deg * pi / 180;
}

double GetRandomNumber(double min, double max) {
	return min + (max - min) * (random() / (RAND_MAX + 1.0)) ;
}

double Clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}
