#include "obj_loader.h"

int OBJLoader::loadFile(const char* path) {
  std::ifstream fileStream(path);

  if (!fileStream) {
    this->error = "Could not open file";
    return -1;
  }

  std::string lineString;
  size_t lineNum = 1;
  while (std::getline(fileStream, lineString)) {
    std::stringstream ss(lineString);
    std::string operation;

    ss >> operation;

    if (operation == "o") {
      this->name = ss.str();
    } else if (operation == "v") {
      this->readVertex(ss);
    } else if (operation == "vt") {
      this->readUV(ss);
    } else if (operation == "vn") {
      this->readNormal(ss);
    } else if (operation == "f") {
      this->readFace(ss);
    }

    if (ss.fail()) {
      this->error = "Failure in reading line " + lineNum;
      return -1;
    }

    lineNum++;
  }

  fileStream.close();
  return 0;
}

void OBJLoader::readVertex(std::stringstream& lineStream) {
  int x, y, z;
  lineStream >> x;
  lineStream >> y;
  lineStream >> z;
  this->vertices.push_back(glm::vec3(x, y, z));
}

void OBJLoader::readUV(std::stringstream& lineStream) {
  int x, y;
  lineStream >> x;
  lineStream >> y;
  this->uvs.push_back(glm::vec2(x, y));
}

void OBJLoader::readNormal(std::stringstream& lineStream) {
  int x, y, z;
  lineStream >> x;
  lineStream >> y;
  lineStream >> z;
  this->vertices.push_back(glm::vec3(x, y, z));
}

void OBJLoader::readFace(std::stringstream& lineStream) {
  
}
