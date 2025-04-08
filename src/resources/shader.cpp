#include "shader.h"

int Shader::load() {
  std::string vertShaderPath = std::string(this->resourcePath);
  vertShaderPath.append(".vert");
  std::string fragShaderPath = std::string(this->resourcePath);
  fragShaderPath.append(".frag");

  std::ifstream vertShaderFile(vertShaderPath), fragShaderFile(fragShaderPath);

  std::string vertexString(
    (std::istreambuf_iterator<char>(vertShaderFile)),
    (std::istreambuf_iterator<char>())
  );

  std::string fragmentString(
    (std::istreambuf_iterator<char>(fragShaderFile)),
    (std::istreambuf_iterator<char>())
  );

  const char* vertexSource = vertexString.c_str();
  const char* fragmentSource = fragmentString.c_str();

  int success;
  char infoLog[512];
  
  GLuint vertex, fragment;

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexSource, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    LOG_ERROR("Vertex shader failed to compile: %s", infoLog);
  } else {
    LOG_DEBUG("Vertex shader successfully compiled");
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentSource, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    LOG_ERROR("Fragment shader failed to compile: %s", infoLog);
  } else {
    LOG_DEBUG("Fragment shader successfully compiled");
  }

  program = glCreateProgram();
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);
  glBindFragDataLocation(program, 0, "fragColor");
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(program, 512, NULL, infoLog);
    LOG_ERROR("Shader program failed to link: %s", infoLog);
  } else {
    LOG_DEBUG("Shader program successfully linked");
  }

  glDetachShader(program, vertex);
  glDetachShader(program, fragment);
  
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  LOG_DEBUG("Shader loaded: %s, %s", vertShaderPath.c_str(), fragShaderPath.c_str());
  return 0;
}

void Shader::unload() {
  LOG_DEBUG("Shader unloaded: %s", resourcePath);
}

GLuint Shader::getUniformLocation(const char* uniform) {
  return glGetUniformLocation(program, uniform);
}

void Shader::setUniformVec3(const char* uniformName, GLfloat x, GLfloat y, GLfloat z) {
  glUniform3f(this->getUniformLocation(uniformName), x, y, z);
}

void Shader::setUniformVec3(const char* uniformName, const glm::vec3& vec) {
  glUniform3fv(this->getUniformLocation(uniformName), 1, &vec[0]);
}

void Shader::setUniformFloat(const char* uniformName, GLfloat f) {
  glUniform1f(this->getUniformLocation(uniformName), f);
}
