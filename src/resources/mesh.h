#ifndef _MESH_H_
#define _MESH_H_

#include <fstream>
#include <cstring>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "resource.h"

class Mesh : public Resource {
	public:
		vector<glm::vec3> vertices;
		vector<glm::vec2> uvs;
		vector<glm::vec3> normals;
		vector<unsigned int> vertexIndices, uvIndices, normalIndices;

		unsigned int vbo, ebo, vao;
		bool assigned = false;

		int load();
		void unload();
};

#endif