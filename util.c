#include <math.h>
#include <stdio.h>

#include "util.h"

void voltage_to_str(char *buf, float v) {
	unsigned char whole;
	unsigned char fraction;

	whole = (v < 100) ? v : 99;
	fraction = (v < 100) ? roundf((v - whole) * 100) : 99;

	sprintf(buf, "%d.%02d", whole, fraction);
}
