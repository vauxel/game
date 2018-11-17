#include "mesh.h"

int Mesh::load() {
    FILE* file = fopen(resourcePath.c_str(), "r");

    if(file == NULL) {
        printf("File failed to be opened\n");
        return -1;
    }

    vector<Vector3> temp_vertices;
    vector<Vector2> temp_uvs;
    vector<Vector3> temp_normals;

    while(true) {
        char line[256];
        int result = fscanf(file, "%s", line);

        if(result == EOF) {
            break;
        }

        if(strcmp(line, "v") == 0) {
            Vector3 vertex;
            fscanf(file, "%lf %lf %lf\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if(strcmp(line, "vt") == 0) {
            Vector2 uv;
            fscanf(file, "%lf %lf\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        } else if(strcmp(line, "vn") == 0) {
            Vector3 normal;
            fscanf(file, "%lf %lf %lf\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if(strcmp(line, "f") == 0) {
            string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

            if(matches != 9) {
                printf("File failed to be parsed\n");
                return -1;
            }

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }

    for(unsigned int i = 0; i < vertexIndices.size(); i++) {
        unsigned int index = vertexIndices[i];
        Vector3 vertex = temp_vertices[index - 1];
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < uvIndices.size(); i++) {
        unsigned int index = uvIndices[i];
        Vector2 uv = temp_uvs[index - 1];
        uvs.push_back(uv);
    }

    for(unsigned int i = 0; i < normalIndices.size(); i++) {
        unsigned int index = normalIndices[i];
        Vector3 normal = temp_normals[index - 1];
        normals.push_back(normal);
    }

    return 0;
}

void Mesh::unload() {
    
}