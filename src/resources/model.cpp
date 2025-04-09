#include "model.h"

int Model::load() {
  int ret = -1;

  if (this->loadingMethod == LoadingMethod::OBJ) {
    OBJLoader loader;

    if (loader.loadOBJFile(resourcePath)) {
      LOG_ERROR("Failed to initialize model: %s (%s)", resourcePath, loader.getError());
      return -1;
    }

    ret = this->initFromOBJ(loader);
  } else if (this->loadingMethod == LoadingMethod::NXM)

  if (ret == 0) {
    LOG_DEBUG("Model loaded: %s", resourcePath);
  }

  return ret;
}

void Model::unload() {
  delete[] this->meshes;
  this->meshes = nullptr;

  for (size_t i = 0; i < this->numMaterials; i++) {
    delete this->materials[i];
  }

  delete[] this->materials;
  this->materials = nullptr;

  LOG_DEBUG("Model unloaded: %s", resourcePath);
}

int Model::initFromOBJ(OBJLoader& objLoader) {
  auto loadedMeshes = objLoader.getMeshes();
  this->numMeshes = loadedMeshes.size();
  this->meshes = new Model::Mesh[this->numMeshes];

  auto loadedMaterials = objLoader.getMaterials();
  this->numMaterials = loadedMaterials.size();
  this->materials = new MaterialData*[this->numMaterials];

  for (size_t i = 0; i < numMeshes; i++) {
    MeshData* newMeshData = new MeshData{
      .vertices = std::move(loadedMeshes[i]->vertices),
      .indices = std::move(loadedMeshes[i]->indices)
    };
    this->meshes[i].init(newMeshData, loadedMeshes[i]->materialData);
  }

  unsigned int meshIndex = 0;
  for (auto& [key, value] : loadedMaterials) {
    this->materials[meshIndex] = value;
    ++meshIndex;
  }

  return 0;
}

void Model::Mesh::init(MeshData* meshData, MaterialData* matData) {
  this->meshData = meshData;
  this->materialData = matData;

  indicesCount = meshData->indices.size();

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(Vertex) * meshData->vertices.size(),
    &meshData->vertices.front(),
    GL_STATIC_DRAW
  );

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    sizeof(unsigned int) * meshData->indices.size(),
    &meshData->indices.front(),
    GL_STATIC_DRAW
  );
}

Model::Mesh::Mesh() {
  vbo = GL_INVALID_VALUE;
  ebo = GL_INVALID_VALUE;
  indicesCount = 0;
}

Model::Mesh::~Mesh() {
  if (vbo != GL_INVALID_VALUE) {
    glDeleteBuffers(1, &vbo);
  }

  if (ebo != GL_INVALID_VALUE) {
    glDeleteBuffers(1, &ebo);
  }

  delete this->meshData;
}
