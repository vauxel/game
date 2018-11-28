#ifndef _SPATIAL_H_
#define _SPATIAL_H_

#include "data/vectors.h"
#include "data/quaternion.h"

typedef struct Spatial {
	Vector3 position;
	Quaternion rotation;
	Vector3 velocity;
	Quaternion angularVel;
} Spatial;

#endif