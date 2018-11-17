#ifndef _MESH_H_
#define _MESH_H_

#include <fstream>
#include <cstring>
#include <vector>
#include "data/vectors.h"
#include "resource.h"

class Mesh : public Resource {
	public:
        vector<Vector3> vertices;
        vector<Vector2> uvs;
        vector<Vector3> normals;
        vector<unsigned int> vertexIndices, uvIndices, normalIndices;

        unsigned int vbo, vao;
        
		int load();
		void unload();
};

#endif