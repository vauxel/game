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
  float ambientCoefficient;

  float coneAngle;
  glm::vec3 coneDirection;

  // Directional
  Light(
    Type type,
    glm::vec3 intensities,
    float ambientCoefficient
  ): type(type), intensities(intensities), ambientCoefficient(ambientCoefficient) {};

  // Point
  Light(
    Type type,
    glm::vec3 intensities,
    float attenuation,
    float ambientCoefficient
  ): type(type), intensities(intensities), attenuation(attenuation), ambientCoefficient(ambientCoefficient) {};

  // Spot
  Light(
    Type type,
    glm::vec3 intensities,
    float attenuation,
    float ambientCoefficient,
    float coneAngle,
    glm::vec3 coneDirection
  ): type(type), intensities(intensities), attenuation(attenuation), ambientCoefficient(ambientCoefficient), coneAngle(coneAngle), coneDirection(coneDirection) {};
};
