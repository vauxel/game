#ifndef _EULER_H_
#define _EULER_H_

#include <math.h>
#include "matrices.h"

typedef struct Quaternion {
	double w, x, y, z;

	Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {};
	Quaternion(double roll, double pitch, double yaw);
	Quaternion() : w(0.0), x(0.0), y(0.0), z(0.0) {};

	Quaternion operator + (const Quaternion&);
	Quaternion operator - (const Quaternion&);
	Quaternion operator * (const Quaternion&);
	Quaternion operator * (const double);

	Matrix matrix4();
} Quaternion;

#endif