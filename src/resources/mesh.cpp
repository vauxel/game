#include "mesh.h"

int Mesh::load() {
	FILE* file = fopen(resourcePath.c_str(), "r");

	if(file == NULL) {
		printf("File failed to be opened\n");
		return -1;
	}

	//std::vector<glm::vec3> temp_vertices;
	//std::vector<glm::vec2> temp_uvs;
	//std::vector<glm::vec3> temp_normals;

	while(true) {
		char line[256];
		int result = fscanf(file, "%s", line);

		if(result == EOF) {
			break;
		}

		if(strcmp(line, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		} else if(strcmp(line, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back(uv);
		} else if(strcmp(line, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		} else if(strcmp(line, "f") == 0) {
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

			if(matches != 9) {
				printf("File failed to be parsed\n");
				return -1;
			}

			vertexIndices.push_back(vertexIndex[0] - 1);
			vertexIndices.push_back(vertexIndex[1] - 1);
			vertexIndices.push_back(vertexIndex[2] - 1);
			uvIndices.push_back(uvIndex[0] - 1);
			uvIndices.push_back(uvIndex[1] - 1);
			uvIndices.push_back(uvIndex[2] - 1);
			normalIndices.push_back(normalIndex[0] - 1);
			normalIndices.push_back(normalIndex[1] - 1);
			normalIndices.push_back(normalIndex[2] - 1);
		} else {
			char discardBuffer[1000];
			fgets(discardBuffer, 1000, file);
		}
	}

	/*for(unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		vertices.push_back(vertex);
		uvs.push_back(uv);
		normals.push_back(normal);
	}*/

	fclose(file);
	return 0;
}

void Mesh::unload() {
	
}