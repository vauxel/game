#pragma once

#define _GNU_SOURCE

#include <iostream>
#include <string>
#include <cstring>
#include <cfloat>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include "logger.h"
#include "model/vertex.h"
#include "model/material.h"

#define IS_SPACE(x) (x == ' ' || x == '\t')

class OBJLoader {
  private:
    enum class TurnDirection {
      Right  = 1,
      Left   = -1,
      NoTurn = 0
    };

    struct MeshData {
      std::vector<Vertex> vertices;
      std::vector<unsigned int> indices;
      std::string objName = "";
      std::string mtlName = "";
      MaterialData* materialData = nullptr;
    };

    struct FaceTripleData {
      int vertIndex;
      int uvIndex;
      int normIndex;

      bool operator==(const FaceTripleData& other) const {
        return vertIndex == other.vertIndex && uvIndex == other.uvIndex && normIndex == other.normIndex;
      }
    };

    struct FaceTripleDataHash {
      size_t operator()(const FaceTripleData& x) const {
        size_t res = 17;
        res = res * 31 + std::hash<int>()(x.vertIndex);
        res = res * 31 + std::hash<int>()(x.uvIndex);
        res = res * 31 + std::hash<int>()(x.normIndex);
        return res;
      }
    };

    const char* error = nullptr;

    std::string mtlLibName = "";

    std::vector<OBJLoader::MeshData*> meshes;
    std::unordered_map<std::string, MaterialData*> materials;

    std::vector<glm::vec3> rawVertices;
    std::vector<glm::vec2> rawUVs;
    std::vector<glm::vec3> rawNormals;

    float parseFloat(const char** token);
    int parseInt(const char** token);
    bool parseFaceTriple(const char** token, int& vIdx, int& uvIdx, int& normIdx);
    unsigned int resolveVertex(OBJLoader::MeshData* mesh, std::unordered_map<FaceTripleData, unsigned int, FaceTripleDataHash>& vertexMap, FaceTripleData& originalIndices);
    void triangulateFace(OBJLoader::MeshData* mesh, std::vector<FaceTripleData>& faceTriples);
    void triangulateFaceFan(std::vector<FaceTripleData>& faceTriples);
    void triangulateFaceEarcut(std::vector<FaceTripleData>& faceTriples, std::vector<glm::vec3>& polyPoints, const glm::vec3& normalPoint);
    bool isConvexPoly(const std::vector<glm::vec3>& points, const glm::vec3& normal);
    glm::vec3 calcPolyNormal(const std::vector<glm::vec3>& points);
    OBJLoader::TurnDirection calcPolyTurnDir(const glm::vec3& prev, const glm::vec3& curr, const glm::vec3& next, const glm::vec3& normal);
    void flushMeshData(OBJLoader::MeshData** mesh);
    void flushMaterialData(MaterialData** material);
    void linkMeshMaterials();
  public:
    int loadOBJFile(const char* path);
    int loadMTLLib(const char* path);
    bool hasMTLLib() { return this->mtlLibName != ""; };
    const char* getError() { return this->error; };
    const std::vector<OBJLoader::MeshData*>& getMeshes() { return this->meshes; };
    const std::unordered_map<std::string, MaterialData*>& getMaterials() { return this->materials; };

    ~OBJLoader();
};
