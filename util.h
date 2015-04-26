#ifndef UTIL_H_
#define UTIL_H_

inline float map(unsigned int input, unsigned int in_min, unsigned int in_max, float out_min, float out_max) {
    return (((out_max - out_min) / (in_max - in_min)) * input) + in_min;
}

/*
* Convert voltage float to voltage string
* Stores result in buf. Max length of buf is 6 (5 characters + null)
*/
void voltage_to_str(char *buf, float v);

#endif /* UTIL_H_ */
