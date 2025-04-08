#pragma once

#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include "util/logger.h"
#include "resource.h"

class Shader : public Resource {
  public:
    GLuint program;
    
    int load();
    void unload();
    GLuint getUniformLocation(const char* uniformName);

    void setUniformVec3(const char* uniformName, GLfloat x, GLfloat y, GLfloat z);
    void setUniformVec3(const char* uniformName, const glm::vec3& vec);
    void setUniformFloat(const char* uniformName, GLfloat f);
};
