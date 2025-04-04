#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <mapbox/earcut.hpp>
#include "model/vertex.h"

#define IS_SPACE(x) (x == ' ' || x == '\t')

class OBJLoader {
  private:
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

    std::string mtlLibName = "";
    std::vector<MeshData*> meshes;

    float parseFloat(const char** token);
    bool parseFaceTriple(const char** token, int& vIdx, int& uvIdx, int& normIdx);
    void resolveVertex(MeshData* mesh, glm::vec3& originalIndices, unsigned int& vertexIndex);
    void flushMeshData(MeshData** mesh, std::vector<MeshData*>& meshes);
  public:
    int loadOBJFile(const char* path);
    const char* getError() { return this->error; };
    const std::vector<MeshData*>& getMeshes() { return this->meshes; };

    ~OBJLoader();
};
