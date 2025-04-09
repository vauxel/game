#pragma once

#include <vector>
#include "vertex.h"

struct MeshData {
  const std::vector<Vertex> vertices;
  const std::vector<unsigned int> indices;
};
