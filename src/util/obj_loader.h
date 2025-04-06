#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cfloat>
#include <sstream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <mapbox/earcut.hpp>
#include "logger.h"
#include "model/vertex.h"

#define IS_SPACE(x) (x == ' ' || x == '\t')

class OBJLoader {
  private:
    enum class TurnDirection {
      Right  = 1,
      Left   = -1,
      NoTurn = 0
    };

    const char* error = nullptr;

    struct MeshData {
      std::vector<glm::vec3> rawVertices;
      std::vector<glm::vec2> rawUVs;
      std::vector<glm::vec3> rawNormals;
      std::vector<Vertex> vertices;
      std::vector<unsigned int> indices;
      std::string objName = "";
      std::string mtlName = "";
    };

    struct FaceTripleData {
      int vertIndex;
      int uvIndex;
      int normIndex;
    };

    std::string mtlLibName = "";
    std::vector<MeshData*> meshes;

    float parseFloat(const char** token);
    bool parseFaceTriple(const char** token, int& vIdx, int& uvIdx, int& normIdx);
    void resolveVertex(MeshData* mesh, FaceTripleData& originalIndices, unsigned int& vertexIndex);
    void triangulateFace(MeshData* mesh, std::vector<FaceTripleData>& faceTriples);
    void triangulateFaceFan(std::vector<FaceTripleData>& faceTriples);
    void triangulateFaceEarcut(std::vector<FaceTripleData>& faceTriples, std::vector<glm::vec3>& polyPoints, const glm::vec3& normalPoint);
    bool isConvexPoly(const std::vector<glm::vec3>& points, const glm::vec3& normal);
    glm::vec3 calcPolyNormal(const std::vector<glm::vec3>& points);
    OBJLoader::TurnDirection calcPolyTurnDir(const glm::vec3& prev, const glm::vec3& curr, const glm::vec3& next, const glm::vec3& normal);
    void flushMeshData(MeshData** mesh, std::vector<MeshData*>& meshes);
  public:
    int loadOBJFile(const char* path);
    const char* getError() { return this->error; };
    const std::vector<MeshData*>& getMeshes() { return this->meshes; };

    ~OBJLoader();
};
