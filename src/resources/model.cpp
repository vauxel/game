#include "model.h"

int Model::load() {
	OBJLoader loader;

	if (loader.loadOBJFile(resourcePath)) {
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
	delete[] this->meshes;
	this->meshes = nullptr;
	LOG_DEBUG("Model unloaded: %s", resourcePath);
}

int Model::init(OBJLoader& objLoader) {
	auto meshData = objLoader.getMeshes();
	this->meshes = new Model::Mesh[meshData.size()];
	this->numMeshes = meshData.size();

	for (unsigned long i = 0; i < numMeshes; i++) {
		this->meshes[i].init(meshData[i]->vertices, meshData[i]->indices);
	}

	return 0;
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