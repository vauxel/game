#pragma once

#include <fstream>
#include <cstring>
#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "util/logger.h"
#include "resource.h"
#include "model/vertex.h"
#include "model/mesh.h"
#include "util/obj_loader.h"

class Model : public Resource {
  public:
    enum class LoadingMethod {
      NXM, // Nexus Model
      OBJ // Wavefront OBJ
    };

    struct Mesh {
      Mesh();
      ~Mesh();

      void init(MeshData* meshData, MaterialData* matData);

      unsigned int vao, vbo, ebo;
      unsigned int indicesCount;

      MeshData* meshData = nullptr;
      MaterialData* materialData = nullptr;
    };

    LoadingMethod loadingMethod;

    Mesh* meshes;
    unsigned int numMeshes = 0;

    MaterialData** materials;
    unsigned int numMaterials = 0;

    Model() {
      this->loadingMethod = LoadingMethod::NXM;
    }

    Model(LoadingMethod loadingMethod) {
      this->loadingMethod = loadingMethod;
    };

    int load();
    void unload();
  private:
    int initFromOBJ(OBJLoader& objReader);
};
