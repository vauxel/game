#ifndef _EULER_H_
#define _EULER_H_

typedef struct Euler3 {
	double roll;
	double pitch;
	double yaw;

	Euler3(double r, double p, double y) : roll(r), pitch(p), yaw(y) {};
	Euler3() : roll(0.0), pitch(0.0), yaw(0.0) {};
} Euler3;

#endif