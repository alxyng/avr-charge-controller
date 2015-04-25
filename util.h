#ifndef UTIL_H_
#define UTIL_H_

inline float map(unsigned int input, unsigned int in_min, unsigned int in_max, float out_min, float out_max) {
    return (((out_max - out_min) / (in_max - in_min)) * input) + in_min;
}

#endif /* UTIL_H_ */
