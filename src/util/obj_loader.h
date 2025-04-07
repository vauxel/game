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

    struct MeshData {
      std::vector<Vertex> vertices;
      std::vector<unsigned int> indices;
      std::string objName = "";
      std::string mtlName = "";
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

    struct MaterialData {
      std::string mtlName = "";

      float colorAmbientR = 0.2;
      float colorAmbientG = 0.2;
      float colorAmbientB = 0.2;

      float colorDiffuseR = 0.8;
      float colorDiffuseG = 0.8;
      float colorDiffuseB = 0.8;

      std::string colorDiffuseMapName = "";

      float colorSpecularR = 1.0;
      float colorSpecularG = 1.0;
      float colorSpecularB = 1.0;

      float dissolve = 1.0;

      float opticalDensity = 1.0;

      // 0  = Color on and Ambient off
      // 1  = Color on and Ambient on
      // 2  = Highlight on
      // 3  = Reflection on and Ray trace on
      // 4  = Transparency: Glass on, Reflection: Ray trace on
      // 5  = Reflection: Fresnel on and Ray trace on
      // 6  = Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
      // 7  = Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
      // 8  = Reflection on and Ray trace off
      // 9  = Transparency: Glass on, Reflection: Ray trace off
      // 10 = Casts shadows onto invisible surfaces
      int illumination = 0;

      float shininess = 0.0;

      float transmissionFilterR = 1.0;
      float transmissionFilterG = 1.0;
      float transmissionFilterB = 1.0;
    };

    const char* error = nullptr;

    std::string mtlLibName = "";

    std::vector<MeshData*> meshes;
    std::unordered_map<std::string, MaterialData*> materials;

    std::vector<glm::vec3> rawVertices;
    std::vector<glm::vec2> rawUVs;
    std::vector<glm::vec3> rawNormals;

    float parseFloat(const char** token);
    int parseInt(const char** token);
    bool parseFaceTriple(const char** token, int& vIdx, int& uvIdx, int& normIdx);
    unsigned int resolveVertex(MeshData* mesh, std::unordered_map<FaceTripleData, unsigned int, FaceTripleDataHash>& vertexMap, FaceTripleData& originalIndices);
    void triangulateFace(MeshData* mesh, std::vector<FaceTripleData>& faceTriples);
    void triangulateFaceFan(std::vector<FaceTripleData>& faceTriples);
    void triangulateFaceEarcut(std::vector<FaceTripleData>& faceTriples, std::vector<glm::vec3>& polyPoints, const glm::vec3& normalPoint);
    bool isConvexPoly(const std::vector<glm::vec3>& points, const glm::vec3& normal);
    glm::vec3 calcPolyNormal(const std::vector<glm::vec3>& points);
    OBJLoader::TurnDirection calcPolyTurnDir(const glm::vec3& prev, const glm::vec3& curr, const glm::vec3& next, const glm::vec3& normal);
    void flushMeshData(MeshData** mesh);
    void flushMaterialData(MaterialData** material);
  public:
    int loadOBJFile(const char* path);
    int loadMTLLib(const char* path);
    bool hasMTLLib() { return this->mtlLibName != ""; };
    const char* getError() { return this->error; };
    const std::vector<MeshData*>& getMeshes() { return this->meshes; };

    ~OBJLoader();
};
