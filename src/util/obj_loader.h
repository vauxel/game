#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class OBJLoader {
  private:
    const char* error = nullptr;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::string name = "";

    void readVertex(std::stringstream& lineStream);
    void readUV(std::stringstream& lineStream);
    void readNormal(std::stringstream& lineStream);
    void readFace(std::stringstream& lineStream);
  public:
    int loadFile(const char* path);
    const char* getError() { return this->error; };
};
