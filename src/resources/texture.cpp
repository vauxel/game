#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.h"

int Texture::load() {
  glGenTextures(1, &this->id);
  glBindTexture(GL_TEXTURE_2D, this->id);

  unsigned char* image = stbi_load(resourcePath, &this->width, &this->height, 0, 3); // 3 = RGB, 4 = RGBA

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGB,
    width,
    height,
    0,
    GL_RGB,
    GL_UNSIGNED_BYTE,
    image
  );

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  stbi_image_free(image);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  LOG_DEBUG("Texture loaded: %s", resourcePath);
  return 0;
}

void Texture::unload() {
  glDeleteTextures(1, &this->id);
  LOG_DEBUG("Texture unloaded: %s", resourcePath);
}

void Texture::bind(GLenum textureUnit) {
  glActiveTexture(textureUnit);
  glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::unbind() {
  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getTexId() {
  return this->id;
}
