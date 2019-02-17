#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <iostream>
#include <GL/glew.h>
#include <SOIL.h>
#include "util/logger.h"
#include "resource.h"

class Texture : public Resource {
	public:
		int load();
		void unload();

		void bind(GLenum textureUnit);
		void unbind();
		unsigned int getTexId();
	private:
		int width, height;
		GLuint id;
};

#endif