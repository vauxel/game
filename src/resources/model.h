#ifndef _MODEL_H_
#define _MODEL_H_

#include <fstream>
#include <cstring>
#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "resource.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 normal;

	Vertex(const glm::vec3& posCoord, const glm::vec2& uvCoord, const glm::vec3& normalCoord) {
		pos = posCoord;
		uv = uvCoord;
		normal = normalCoord;
	}
};

class Model : public Resource {
	public:
		int load();
		void unload();

		struct Mesh {
			Mesh();
			~Mesh();

			void init(const vector<Vertex>& vertices, const vector<unsigned int>& indices);

			unsigned int vao, vbo, ebo;
			unsigned int indicesCount;
		};

		vector<Mesh> meshes;
	private:
		int init(const aiScene* pScene);
		void initMesh(unsigned int index, const aiMesh* paiMesh);
		void clear();
};

#endif