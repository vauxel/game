#include "model.h"

int Model::load() {
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(resourcePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	int ret = -1;

	if(pScene) {
		ret = init(pScene);

		if(ret != 0) {
			LOG_ERROR("Failed to initialize model: %s", resourcePath);
		}
	} else {
		LOG_ERROR("Failed to parse model: %s", importer.GetErrorString());
	}

	LOG_DEBUG("Model loaded: %s", resourcePath);
	return ret;
}

void Model::unload() {
	LOG_DEBUG("Model unloaded: %s", resourcePath);
}

int Model::init(const aiScene* pScene) {
	meshes.resize(pScene->mNumMeshes);

	for(unsigned int i = 0; i < meshes.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		initMesh(i, paiMesh);
	}

	return 0;
}

void Model::initMesh(unsigned int index, const aiMesh* paiMesh) {
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	aiVector3D zero3d(0.0f, 0.0f, 0.0f);

	for(unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		aiVector3D* pPos = &(paiMesh->mVertices[i]);
        aiVector3D* pNormal = &(paiMesh->mNormals[i]);
        aiVector3D* pTexCoord = &(paiMesh->HasTextureCoords(0) ? paiMesh->mTextureCoords[0][i] : zero3d);

		Vertex v(
			glm::vec3(pPos->x, pPos->y, pPos->z),
			glm::vec2(pTexCoord->x, pTexCoord->y),
			glm::vec3(pNormal->x, pNormal->y, pNormal->z)
		);

		vertices.push_back(v);
	}

	for(unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& face = paiMesh->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	meshes[index].init(vertices, indices);
}

void Model::Mesh::init(const vector<Vertex>& vertices, const vector<unsigned int>& indices) {
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
	if(vbo != GL_INVALID_VALUE) {
		glDeleteBuffers(1, &vbo);
	}

	if(ebo != GL_INVALID_VALUE) {
		glDeleteBuffers(1, &ebo);
	}
}