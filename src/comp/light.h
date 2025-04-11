#pragma once

#include <glm/vec3.hpp>
#include "entity.h"

struct Light : public Component {
  enum Type: int {
    DIRECTIONAL,
    POINT,
    SPOT
  };

  Type type;

  glm::vec3 intensities;
  float attenuation;

  float coneAngle;
  glm::vec3 coneDirection;

  // Directional
  Light(
    Type type,
    glm::vec3 intensities
  ): type(type), intensities(intensities) {};

  // Point
  Light(
    Type type,
    glm::vec3 intensities,
    float attenuation
  ): type(type), intensities(intensities), attenuation(attenuation) {};

  // Spot
  Light(
    Type type,
    glm::vec3 intensities,
    float attenuation,
    float coneAngle,
    glm::vec3 coneDirection
  ): type(type), intensities(intensities), attenuation(attenuation), coneAngle(coneAngle), coneDirection(coneDirection) {};
};
