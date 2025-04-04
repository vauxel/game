#include "obj_loader.h"

int OBJLoader::loadOBJFile(const char* path) {
  std::ifstream fileStream(path);

  if (!fileStream) {
    this->error = "Could not open file";
    return -1;
  }

  MeshData* currMesh = new MeshData();

  size_t lineNum = 0;
  while (fileStream.peek() != -1) {
    lineNum++;
    std::string lineBuffer;
    std::getline(fileStream, lineBuffer);

    if (lineBuffer.empty()) {
      continue;
    }

    const char* token = lineBuffer.c_str();
    token += strspn(token, " \t");

    if (token[0] == '\0' || token[0] == '#') {
      continue;
    }

    // Parse material library filename
    if (strncmp(token, "mtllib", 6) == 0 && IS_SPACE(token[6])) {
      token += 7;
      token += strspn(token, " \t");

      this->mtlLibName = std::string(token);

      continue;
    }

    // Parse name
    if (token[0] == 'o' && IS_SPACE(token[1])) {
      token += 1;
      token += strspn(token, " \t");

      currMesh->objName = std::string(token);

      continue;
    }

    // Parse material name
    if (strncmp(token, "usemtl", 6) == 0 && IS_SPACE(token[6])) {
      token += 7;
      token += strspn(token, " \t");

      currMesh->mtlName = std::string(token);

      continue;
    }

    // Parse vertex
    if (token[0] == 'v' && IS_SPACE(token[1])) {
      token += 1;

      float x = parseFloat(&token);
      float y = parseFloat(&token);
      float z = parseFloat(&token);

      currMesh->rawVertices.push_back(glm::vec3(x, y, z));

      continue;
    }

    // Parse UV
    if (token[0] == 'v' && token[1] == 't' && IS_SPACE(token[2])) {
      token += 2;

      float x = parseFloat(&token);
      float y = parseFloat(&token);

      currMesh->rawUVs.push_back(glm::vec2(x, y));

      continue;
    }

    // Parse normal
    if (token[0] == 'v' && token[1] == 'n' && IS_SPACE(token[2])) {
      token += 2;

      float x = parseFloat(&token);
      float y = parseFloat(&token);
      float z = parseFloat(&token);

      currMesh->rawNormals.push_back(glm::vec3(x, y, z));

      continue;
    }

    // Parse face indices
    if (token[0] == 'f' && IS_SPACE(token[1])) {
      token += 1;
      token += strspn(token, " \t");

      std::vector<glm::vec3> faceTriples;

      while (token[0] != '\0') {
        int vIdx = 0, uvIdx = 0, normIdx = 0;

        if (this->parseFaceTriple(&token, vIdx, uvIdx, normIdx)) {
          faceTriples.push_back(glm::vec3(vIdx, uvIdx, normIdx));
          token += strspn(token, " \t");
        }
      }

      if (faceTriples.size() > 3) {
        // TODO: Do triangulation
      }

      for (size_t ti = 0; ti < faceTriples.size(); ti++) {
        unsigned int vertexIndex = 0;
        this->resolveVertex(currMesh, faceTriples[ti], vertexIndex);
        currMesh->indices.push_back(vertexIndex);
      }

      continue;
    }
  }

  this->meshes.push_back(currMesh);

  fileStream.close();
  return 0;
}

float OBJLoader::parseFloat(const char** token) {
  (*token) += strspn(*token, " \t");
  float i = atof(*token);
  (*token) += strcspn(*token, " \t");
  return i;
}

bool OBJLoader::parseFaceTriple(const char** token, int& vIdx, int& uvIdx, int& normIdx) {
  if (IS_SPACE((*token)[0])) {
    return false;
  }

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

void OBJLoader::resolveVertex(MeshData* mesh, glm::vec3& originalIndices, unsigned int& vertexIndex) {
  Vertex newVertex = Vertex(
    mesh->rawVertices[originalIndices.x - 1],
    originalIndices.y != 0 ? mesh->rawUVs[originalIndices.y - 1] : glm::vec3(0, 0, 0),
    originalIndices.z != 0 ? mesh->rawNormals[originalIndices.z - 1] : glm::vec3(0, 0, 0)
  );

  for (size_t i = 0; i < mesh->vertices.size(); i++) {
    if (mesh->vertices[i] == newVertex) {
      vertexIndex = i;
      return;
    }
  }

  mesh->vertices.push_back(newVertex);
  vertexIndex = mesh->vertices.size() - 1;
}

void OBJLoader::flushMeshData(MeshData** mesh, std::vector<MeshData*>& meshes) {
  meshes.push_back(*mesh);
  *mesh = new MeshData();
}

OBJLoader::~OBJLoader() {
  for (size_t i = 0; i < this->meshes.size(); i++) {
    delete this->meshes[i];
  }
}
