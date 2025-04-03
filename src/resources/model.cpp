#include "model.h"

int Model::load() {
	OBJLoader loader;

	if (loader.loadFile(resourcePath)) {
		LOG_ERROR("Failed to initialize model: %s (%s)", resourcePath, loader.getError());
		return -1;
	}

	int ret = this->init(loader);

	if (ret == 0) {
		LOG_DEBUG("Model loaded: %s", resourcePath);
	}

	return ret;
}

void Model::unload() {
	LOG_DEBUG("Model unloaded: %s", resourcePath);
}

int Model::init(OBJLoader& objLoader) {
	meshes = new std::vector<Mesh>(shapes.size());

	for (size_t s = 0; s < meshes->size(); s++) {
		meshes->at(s) = Mesh();
		this->initMesh(shapes[s], attrib, &meshes->at(s));
	}

	return 0;
}

void Model::initMesh(const tinyobj::shape_t& shape, const tinyobj::attrib_t& attrib, Model::Mesh* mesh) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (size_t v = 0; v < attrib.vertices.size(); v += 3) {
		glm::vec3 vertCoord(
			attrib.vertices[v + 0],
			attrib.vertices[v + 1],
			attrib.vertices[v + 2]
		);

		glm::vec3 normCoord;

		normCoord = glm::vec3(
			attrib.normals[v + 0],
			attrib.normals[v + 1],
			attrib.normals[v + 2]
		);

		glm::vec2 texCoord;

		texCoord = glm::vec2(
			attrib.texcoords[v + 0],
			attrib.texcoords[v + 1]
		);

		Vertex vertex(vertCoord, texCoord, normCoord);
		vertices.push_back(vertex);
	}

	for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
		indices.push_back(shape.mesh.indices[3 * f + 0].vertex_index);
		indices.push_back(shape.mesh.indices[3 * f + 1].vertex_index);
		indices.push_back(shape.mesh.indices[3 * f + 2].vertex_index);
	}

	mesh->init(vertices, indices);
}

void Model::Mesh::init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
	indicesCount = indices.size();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(Vertex) * vertices.size(),
		&vertices.front(),
		GL_STATIC_DRAW
	);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned int) * indices.size(),
		&indices.front(),
		GL_STATIC_DRAW
	);
}

Model::Mesh::Mesh() {
	vbo = GL_INVALID_VALUE;
	ebo = GL_INVALID_VALUE;
	indicesCount = 0;
}

Model::Mesh::~Mesh() {
	if (vbo != GL_INVALID_VALUE) {
		glDeleteBuffers(1, &vbo);
	}

	if (ebo != GL_INVALID_VALUE) {
		glDeleteBuffers(1, &ebo);
	}
}