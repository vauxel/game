#ifndef _SPATIAL_H_
#define _SPATIAL_H_

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include "entity.h"

struct Spatial : public Component {
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 velocity;
	glm::quat angularVel;
};

#endif