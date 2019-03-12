#include "render.h"

Render::Render(std::string modelName, std::string texName) {
	model = ResourceManager::instance()->getResource<Model>(modelName);
	texture = ResourceManager::instance()->getResource<Texture>(texName);

	if(model == nullptr) {
		LOG_ERROR("Failed to load render model: %s", modelName.c_str());
	}

	if(texture == nullptr) {
		LOG_ERROR("Failed to load render texture: %s", texName.c_str());
	}
}

void Render::render() {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for(unsigned int i = 0; i < model->meshes.size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, model->meshes[i].vbo);

		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT, GL_FALSE,
			sizeof(Vertex),
			(GLvoid*)offsetof(Vertex, pos)
		);

		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT, GL_FALSE,
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

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->meshes[i].ebo);

		texture->bind(GL_TEXTURE0);

		glDrawElements(
			GL_TRIANGLES,
			model->meshes[i].indicesCount,
			GL_UNSIGNED_INT,
			0
		);

		texture->unbind();
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}