#pragma once

#include <iostream>
#include <GL/glew.h>
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
