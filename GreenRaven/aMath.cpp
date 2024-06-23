#include "aMath.h"
#include <time.h>
#include <cstdlib>
#define PI 3.14159265359 

double drand() {
	srand(time(NULL));
	double out = rand() % 100001;
	out = out / 100000;
	return out;
}

double am::normalRandom() {
	srand(time(NULL));
	double u = drand();
	double v = drand();
	double x = sqrt(-2.0 * log(u)) * cos(2.0 * PI * v);
	if (rand() % 2 == 0) {
		x = -x;
	}
	return x;
}
double am::finiteRandom() {
	double x = normalRandom();
	x = x / 3;
	if (x > 1) {
		x = 0;
	}
	if (x < -1) {
		x = 0;
	}
	return x;
}
int am::clampi(int v, int min, int max) {
	int o = v;
	if (o > max) {
		o = max;
	}
	if (o < min) {
		o = min;
	}
	return o;
}