#include "obj_loader.h"

int OBJLoader::loadOBJFile(const char* path) {
  FILE* file = fopen(path, "r");

  if (file == NULL) {
    this->error = "Could not open file";
    return -1;
  }

  auto t_start = std::chrono::high_resolution_clock::now();

  MeshData* currMesh = new MeshData();
  std::unordered_map<FaceTripleData, unsigned int, FaceTripleDataHash> vertexMap;

  char line[512];
  unsigned int lineNum = 0;
  while (fgets(line, 512, file) != NULL) {
    ++lineNum;

    // if (lineSize == 0) {
    //   continue;
    // }

    const char* token = line;
    token += strspn(token, " \t\n");

    if (token[0] == '\0' || token[0] == '#') {
      continue;
    }

    // Parse material library filename
    if (strncmp(token, "mtllib", 6) == 0 && IS_SPACE(token[6])) {
      token += 7;
      token += strspn(token, " \t");

      this->mtlLibName = std::string(token);
      this->mtlLibName.pop_back(); // Remove newline character

      continue;
    }

    // Parse name
    if (token[0] == 'o' && IS_SPACE(token[1])) {
      token += 1;
      token += strspn(token, " \t");

      currMesh->objName = std::string(token);
      currMesh->objName.pop_back(); // Remove newline character

      if (currMesh->vertices.size() > 0) {
        this->flushMeshData(&currMesh, meshes);
      }

      continue;
    }

    // Parse material name
    if (strncmp(token, "usemtl", 6) == 0 && IS_SPACE(token[6])) {
      token += 7;
      token += strspn(token, " \t");

      currMesh->mtlName = std::string(token);
      currMesh->mtlName.pop_back(); // Remove newline character

      continue;
    }

    // Parse vertex
    if (token[0] == 'v' && IS_SPACE(token[1])) {
      token += 1;

      float x = parseFloat(&token);
      float y = parseFloat(&token);
      float z = parseFloat(&token);

      if (currMesh->vertices.size() > 0) {
        this->flushMeshData(&currMesh, meshes);
      }

      this->rawVertices.push_back(glm::vec3(x, y, z));

      continue;
    }

    // Parse UV
    if (token[0] == 'v' && token[1] == 't' && IS_SPACE(token[2])) {
      token += 2;

      float x = parseFloat(&token);
      float y = parseFloat(&token);

      this->rawUVs.emplace_back(glm::vec2(x, y));

      continue;
    }

    // Parse normal
    if (token[0] == 'v' && token[1] == 'n' && IS_SPACE(token[2])) {
      token += 2;

      float x = parseFloat(&token);
      float y = parseFloat(&token);
      float z = parseFloat(&token);

      this->rawNormals.emplace_back(glm::vec3(x, y, z));

      continue;
    }

    // Parse face indices
    if (token[0] == 'f' && IS_SPACE(token[1])) {
      token += 1;
      token += strspn(token, " \t");

      std::vector<FaceTripleData> faceTriples;

      while (token[0] != '\0') {
        int vIdx = 0, uvIdx = 0, normIdx = 0;

        if (this->parseFaceTriple(&token, vIdx, uvIdx, normIdx)) {
          if (vIdx <= 0 || uvIdx <= 0 || normIdx <= 0) {
            this->error = "Unable to parse face with negative index(es)";
            fclose(file);
            return -1;
          }

          faceTriples.push_back({ vIdx, uvIdx, normIdx });
          token += strspn(token, " \t\n");
        }
      }

      const size_t numFaceTriples = faceTriples.size();

      if (numFaceTriples < 3) {
        LOG_WARNING("Degenerated face found in OBJ file \"%s\" on line %u", path, lineNum);
        continue;
      }

      if (numFaceTriples > 3) {
        this->triangulateFace(currMesh, faceTriples);

        if (faceTriples.size() % 3 != 0) {
          LOG_WARNING("Failed to triangulate %lu-gon face in OBJ file \"%s\" on line %u", static_cast<unsigned long>(numFaceTriples), path, lineNum);
          continue;
        }
      }

      for (size_t ti = 0; ti < faceTriples.size(); ti++) {
        unsigned int vertexIndex = this->resolveVertex(currMesh, vertexMap, faceTriples[ti]);
        currMesh->indices.emplace_back(vertexIndex);
      }

      continue;
    }
  }

  this->meshes.emplace_back(currMesh);

  auto t_end = std::chrono::high_resolution_clock::now();
  double elapsedTime = std::chrono::duration<double, std::milli>(t_end - t_start).count();

  LOG_DEBUG("Loading %s OBJ file took %fms", path, elapsedTime);

  fclose(file);
  return 0;
}

inline float OBJLoader::parseFloat(const char** token) {
  (*token) += strspn(*token, " \t");
  float i = atof(*token);
  (*token) += strcspn(*token, " \t");
  return i;
}

bool OBJLoader::parseFaceTriple(const char** token, int& vIdx, int& uvIdx, int& normIdx) {
  vIdx = atoi(*token);
  (*token) += strcspn(*token, "/ \t");

  // i
  if ((*token)[0] != '/') {
    return true;
  }

  (*token)++;

  // i//k
  if ((*token)[0] == '/') {
    (*token)++;
    normIdx = atoi(*token);
    (*token) += strcspn(*token, "/ \t");
  } else {
    // i/j
    uvIdx = atoi(*token);
    (*token) += strcspn(*token, "/ \t");
    
    // i/j/k
    if ((*token)[0] == '/') {
      (*token)++;
      normIdx = atoi(*token);
      (*token) += strcspn(*token, " \t");
    }
  }

  return true;
}

unsigned int OBJLoader::resolveVertex(MeshData* mesh, std::unordered_map<FaceTripleData, unsigned int, FaceTripleDataHash>& vertexMap, FaceTripleData& originalIndices) {
  if (auto search = vertexMap.find(originalIndices); search != vertexMap.end()) {
    return search->second;
  } else {
    Vertex newVertex = Vertex(
      this->rawVertices[originalIndices.vertIndex - 1],
      originalIndices.uvIndex != 0 ? this->rawUVs[originalIndices.uvIndex - 1] : glm::vec3(0, 0, 0),
      originalIndices.normIndex != 0 ? this->rawNormals[originalIndices.normIndex - 1] : glm::vec3(0, 0, 0)
    );

    mesh->vertices.emplace_back(newVertex);
    unsigned int vertexIndex = static_cast<unsigned int>(mesh->vertices.size()) - 1;
    vertexMap.emplace(originalIndices, vertexIndex);
    return vertexIndex;
  }
}

void OBJLoader::triangulateFace(MeshData* mesh, std::vector<FaceTripleData>& faceTriples) {
  std::vector<glm::vec3> polyPoints;

  for (size_t i = 0; i < faceTriples.size(); i++) {
    polyPoints.emplace_back(this->rawVertices[faceTriples[i].vertIndex - 1]);
  }

  const glm::vec3 normal = this->calcPolyNormal(polyPoints);

  if (this->isConvexPoly(polyPoints, normal)) {
    this->triangulateFaceFan(faceTriples);
  } else {
    this->triangulateFaceEarcut(faceTriples, polyPoints, normal);
  }
}

inline glm::vec3 OBJLoader::calcPolyNormal(const std::vector<glm::vec3>& points) {
  glm::vec3 normal(0.0, 0.0, 0.0);
  const size_t n = points.size();

  for (size_t i = 0; i < n; i++) {
    const glm::vec3& curr = points[i % n];
    const glm::vec3& next = points[(i + 1) % n];

    normal.x += (next.y - curr.y) * (next.z + curr.z);
    normal.y += (next.z - curr.z) * (next.x + curr.x);
    normal.z += (next.x - curr.x) * (next.y + curr.y);
  }

  return glm::normalize(normal);
}

inline OBJLoader::TurnDirection OBJLoader::calcPolyTurnDir(const glm::vec3& prev, const glm::vec3& curr, const glm::vec3& next, const glm::vec3& normal) {
  const float dot = glm::dot(glm::cross(next - prev, glm::normalize(curr - prev)), normal);

  if (dot > +0.001) {
    return TurnDirection::Right;
  } else if (dot < -0.001) {
    return TurnDirection::Left;
  } else {
    return TurnDirection::NoTurn;
  }
}

bool OBJLoader::isConvexPoly(const std::vector<glm::vec3>& points, const glm::vec3& normal) {
  const size_t n = points.size();
  TurnDirection polyTurnDir = TurnDirection::NoTurn;

  for (size_t i = 0; i < n; i++) {
    const glm::vec3& prev = points[(i - 1 + n) % n];
    const glm::vec3& curr = points[i % n];
    const glm::vec3& next = points[(i + 1) % n];

    TurnDirection turnDir = this->calcPolyTurnDir(prev, curr, next, normal);

    if (turnDir == TurnDirection::NoTurn) {
      continue;
    }

    if (polyTurnDir == TurnDirection::NoTurn) {
      polyTurnDir = turnDir;
    }

    if (polyTurnDir != turnDir) {
      return false;
    }
  }

  return true;
}

void OBJLoader::triangulateFaceFan(std::vector<FaceTripleData>& faceTriples) {
  std::vector<FaceTripleData> newFaceTriples;

  for (size_t i = 1; i < faceTriples.size() - 1; i++) {
    newFaceTriples.emplace_back(faceTriples[0]);
    newFaceTriples.emplace_back(faceTriples[i]);
    newFaceTriples.emplace_back(faceTriples[i + 1]);
  }

  faceTriples = std::move(newFaceTriples);
}

void OBJLoader::triangulateFaceEarcut(std::vector<FaceTripleData>& faceTriples, std::vector<glm::vec3>& polyPoints, const glm::vec3& normalPoint) {
  std::vector<FaceTripleData> newFaceTriples;

  // Calculate and align clockwise-ness
  {
    const size_t n = polyPoints.size();
    double orientationSum = 0.0;

    for (size_t i = 0; i < n; i++) {
      const glm::vec3& prev = polyPoints[(i - 1 + n) % n];
      const glm::vec3& curr = polyPoints[i % n];
      const glm::vec3& next = polyPoints[(i + 1) % n];

      const glm::vec3 cross = glm::cross(curr - prev, next - curr);
      orientationSum += glm::dot(cross, normalPoint);
    }

    bool isClockwise = orientationSum < 0.0;

    if (!isClockwise) {
      faceTriples = {faceTriples.rbegin(), faceTriples.rend()};
      polyPoints = {polyPoints.rbegin(), polyPoints.rend()};
    }
  }

  while (!polyPoints.empty()) {
    int earIndex = -1;

    // Get biggest ear
    {
      const size_t n = polyPoints.size();
      
      if (n == 3) {
        earIndex = 0;
      } else if (n == 0) {
        earIndex = -1;
      } else {
        double maxArea = DBL_MIN;

        for (size_t i = 0; i < n; i++) {
          bool isEar = true;

          // Detect if ear
          {
            const size_t n = polyPoints.size();

            if (n < 3) {
              isEar = false;
            } else if (n == 3) {
              isEar = true;
            } else {
              const int prevIndex = (i - 1 + n) % n;
              const int currIndex = i % n;
              const int nextIndex = (i + 1) % n;

              const glm::vec3& prev = polyPoints[prevIndex];
              const glm::vec3& curr = polyPoints[currIndex];
              const glm::vec3& next = polyPoints[nextIndex];

              if (this->calcPolyTurnDir(prev, curr, next, normalPoint) != TurnDirection::Right) {
                isEar = false;
              } else {
                for (size_t j = 0; j < polyPoints.size(); j++) {
                  if (j == prevIndex || j == currIndex || j == nextIndex) {
                    continue;
                  }

                  bool pointInsideOrEdgeTriangle = false;

                  // Detect if the point is inside or edge of the triangle
                  {
                    static double zero = std::numeric_limits<double>::epsilon();

                    const glm::vec3 v0 = next - prev;
                    const glm::vec3 v1 = curr - prev;
                    const glm::vec3 v2 = polyPoints[j] - prev;

                    const float dot00 = glm::dot(v0, v0);
                    const float dot01 = glm::dot(v0, v1);
                    const float dot02 = glm::dot(v0, v2);
                    const float dot11 = glm::dot(v1, v1);
                    const float dot12 = glm::dot(v1, v2);

                    const float denom = dot00 * dot11 - dot01 * dot01;

                    if (!(std::abs(denom) < zero)) {
                      const double invDenom = 1.0 / denom;
                      const double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
                      const double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

                      pointInsideOrEdgeTriangle = (u >= 0.0) && (v >= 0.0) && (u + v < 1.0);
                    }
                  }

                  if (pointInsideOrEdgeTriangle) {
                    isEar = false;
                    break;
                  }
                }
              }
            }
          }

          if (!isEar) {
            continue;
          }

          const glm::vec3& prev = polyPoints[(i - 1 + n) % n];
          const glm::vec3& curr = polyPoints[i % n];
          const glm::vec3& next = polyPoints[(i + 1) % n];

          const auto cross = glm::cross(curr - prev, next - prev);
          const float area = (cross.x * cross.x + cross.y * cross.y + cross.z * cross.z) / 4.0f;

          if (area > maxArea) {
            earIndex = i;
            maxArea = area;
          }
        }
      }
    }

    // Fallback to getting overlapping ear
    if (earIndex == -1) {
      const size_t n = polyPoints.size();

      if (n == 3) {
        earIndex = 0;
      } else if (n == 0) {
        earIndex = -1;
      } else {
        for (size_t i = 0; i < n; i++) {
          const glm::vec3& prev = polyPoints[(i - 1 + n) % n];
          const glm::vec3& curr = polyPoints[i % n];
          const glm::vec3& next = polyPoints[(i + 1) % n];

          if (this->calcPolyTurnDir(prev, curr, next, normalPoint) != TurnDirection::NoTurn) {
            continue;
          }

          if (glm::dot(glm::normalize(curr - prev), glm::normalize(next - curr)) < 0.0) {
            earIndex = i;
            break;
          }
        }
      }
    }

    if (earIndex == -1) {
      faceTriples.clear();
      return;
    }

    const size_t n = faceTriples.size();

    const int prevIndex = (earIndex - 1 + n) % n;
    const int currIndex = earIndex % n;
    const int nextIndex = (earIndex + 1) % n;

    // const glm::vec3& prevPoint = polyPoints[prevIndex];
    // const glm::vec3& currPoint = polyPoints[currIndex];
    // const glm::vec3& nextPoint = polyPoints[nextIndex];

    const FaceTripleData& prevFaceTriple = faceTriples[prevIndex];
    const FaceTripleData& currFaceTriple = faceTriples[currIndex];
    const FaceTripleData& nextFaceTriple = faceTriples[nextIndex];

    newFaceTriples.emplace_back(prevFaceTriple);
    newFaceTriples.emplace_back(currFaceTriple);
    newFaceTriples.emplace_back(nextFaceTriple);
    
    polyPoints.erase(polyPoints.begin() + earIndex);
    faceTriples.erase(faceTriples.begin() + earIndex);

    if (polyPoints.size() < 3) {
      break;
    }
  }

  if (polyPoints.size() == 2) {
    faceTriples = std::move(newFaceTriples);
  } else {
    faceTriples.clear();
  }
}

inline void OBJLoader::flushMeshData(MeshData** mesh, std::vector<MeshData*>& meshes) {
  meshes.emplace_back(*mesh);
  *mesh = new MeshData();
}

OBJLoader::~OBJLoader() {
  for (size_t i = 0; i < this->meshes.size(); i++) {
    delete this->meshes[i];
  }
}
