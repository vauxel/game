#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include "entity.h"

struct Spatial : public Component {
  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 velocity;
  glm::quat angularVel;

  Spatial(
    glm::vec3 position,
    glm::quat rotation,
    glm::vec3 velocity,
    glm::quat angularVel
  ): position(position), rotation(rotation), velocity(velocity), angularVel(angularVel) {};

  Spatial(
    glm::vec3 position
  ): position(position), rotation(0.0f, 0.0f, 0.0f, 0.0f), velocity(0.0f), angularVel(0.0f, 0.0f, 0.0f, 0.0f) {};

  Spatial(): position(0.0f), rotation(0.0f, 0.0f, 0.0f, 0.0f), velocity(0.0f), angularVel(0.0f, 0.0f, 0.0f, 0.0f) {};
};
