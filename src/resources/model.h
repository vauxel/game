#pragma once

#include <fstream>
#include <cstring>
#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "util/logger.h"
#include "resource.h"
#include "model/vertex.h"
#include "util/obj_loader.h"

class Model : public Resource {
	public:
		int load();
		void unload();

		struct Mesh {
			Mesh();
			~Mesh();

			void init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

			unsigned int vao, vbo, ebo;
			unsigned int indicesCount;
		};

		Mesh* meshes;
		size_t numMeshes = 0;
	private:
		int init(OBJLoader& objReader);
};
