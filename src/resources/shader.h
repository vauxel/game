#pragma once

#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include "util/logger.h"
#include "resource.h"

class Shader : public Resource {
	public:
		GLuint program;
		
		int load();
		void unload();
		GLuint getUniformLocation(const char* uniform);
};
