#ifndef _SPATIAL_H_
#define _SPATIAL_H_

#include "data/vectors.h"
#include "data/euler.h"

typedef struct Spatial {
	Vector3 position;
	Euler3 rotation;
	Vector3 velocity;
	Euler3 angularVel;
} Spatial;

#endif