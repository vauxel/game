#ifndef _SHADER_H_
#define _SHADER_H_

#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include "resource.h"

class Shader : public Resource {
	public:
		GLuint program;
		
		int load();
		void unload();
		GLuint getUniformLocation(const char* uniform);
};

#endif