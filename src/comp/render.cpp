#include "render.h"

Render::Render(std::string modelName, std::string texName) {
	this->model = ResourceManager::instance()->getResource<Model>(modelName);
	this->texture = ResourceManager::instance()->getResource<Texture>(texName);

	if (this->model == nullptr || this->model == NULL) {
		LOG_ERROR("Failed to get render model: %s", modelName.c_str());
	}

	if (this->texture == nullptr || this->texture == NULL) {
		LOG_ERROR("Failed to get render texture: %s", texName.c_str());
	}

	this->ready = !(this->model == nullptr || this->model == NULL) && !(this->texture == nullptr || this->texture == NULL);
}

void Render::render() {
	if (!this->ready) {
		return;
	}

	// Can potentially optimize by moving the following 3 calls to mesh init only? Possible?
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for(unsigned int i = 0; i < model->meshes->size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, model->meshes->at(i).vbo);

		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(GLvoid*)offsetof(Vertex, pos)
		);

		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(GLvoid*)offsetof(Vertex, uv)
		);

		glVertexAttribPointer(
			2,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(GLvoid*)offsetof(Vertex, normal)
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->meshes->at(i).ebo);

		texture->bind(GL_TEXTURE0 + 0);

		glDrawElements(
			GL_TRIANGLES,
			model->meshes->at(i).indicesCount,
			GL_UNSIGNED_INT,
			0
		);

		texture->unbind();
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}