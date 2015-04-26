#include <math.h>
#include <stdio.h>

#include "util.h"

void voltage_to_str(char *buf, float v) {
	unsigned char whole;
	unsigned char fraction;

	whole = v;
	fraction = roundf((v - whole) * 100);
	if (fraction == 100) { // if fraction ever great than 100, problem!
		fraction = 0;
		whole++;
	}
	if (whole >= 100) {
		whole = 99;
		fraction = 99;
	}

	sprintf(buf, "%d.%02d", whole, fraction);
}
