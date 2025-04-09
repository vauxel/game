#include "render.h"

Render::Render(std::string modelName, std::string texName) {
  this->model = ResourceManager::instance()->getResource<Model>(modelName);
  this->texture = ResourceManager::instance()->getResource<Texture>(texName);

  if (this->model == nullptr || this->model == NULL) {
    LOG_ERROR("Failed to get render model: %s", modelName.c_str());
  }

  if (this->texture == nullptr || this->texture == NULL) {
    LOG_ERROR("Failed to get render texture: %s", texName.c_str());
  }

  this->ready = !(this->model == nullptr || this->model == NULL) && !(this->texture == nullptr || this->texture == NULL);
}

void Render::render(Shader* shader) {
  if (!this->ready) {
    return;
  }

  // Can potentially optimize by moving the following 3 calls to mesh init only? Possible?
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  for (unsigned int i = 0; i < model->numMeshes; i++) {
    Model::Mesh& mesh = model->meshes[i];

    if (mesh.vbo == GL_INVALID_VALUE || mesh.ebo == GL_INVALID_VALUE) {
      continue;
    }

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

    shader->setUniformVec3("material.ambient", mesh.materialData->colorAmbientR, mesh.materialData->colorAmbientG, mesh.materialData->colorAmbientB);
    shader->setUniformVec3("material.diffuse", mesh.materialData->colorDiffuseR, mesh.materialData->colorDiffuseG, mesh.materialData->colorDiffuseB);
    shader->setUniformVec3("material.specular", mesh.materialData->colorSpecularR, mesh.materialData->colorSpecularG, mesh.materialData->colorSpecularB);
    shader->setUniformFloat("material.shininess", mesh.materialData->shininess);

    glVertexAttribPointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (GLvoid*)offsetof(Vertex, pos)
    );

    glVertexAttribPointer(
      1,
      2,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (GLvoid*)offsetof(Vertex, uv)
    );

    glVertexAttribPointer(
      2,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (GLvoid*)offsetof(Vertex, normal)
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->meshes[i].ebo);

    texture->bind(GL_TEXTURE0 + 0);

    glDrawElements(
      GL_TRIANGLES,
      model->meshes[i].indicesCount,
      GL_UNSIGNED_INT,
      0
    );

    texture->unbind();
  }

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}
