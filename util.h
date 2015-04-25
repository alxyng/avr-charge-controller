#ifndef UTIL_H_
#define UTIL_H_

#include <math.h>
#include <stdio.h>

inline float map(unsigned int input, unsigned int in_min, unsigned int in_max, float out_min, float out_max) {
    return (((out_max - out_min) / (in_max - in_min)) * input) + in_min;
}

/*
* Convert voltage float to voltage string
* Stores result in buf. Max length of buf is 6 (5 characters + null)
*/

void voltage_to_str(char *buf, float v) {
	unsigned char whole;
	unsigned char fraction;

	whole = (v < 100) ? v : 99;
	fraction = (v < 100) ? roundf((v - whole) * 100) : 99;

	sprintf(buf, "%d.%02d", whole, fraction);
}

#endif /* UTIL_H_ */
