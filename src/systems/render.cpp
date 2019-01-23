#include "render.h"

RenderSystem::RenderSystem(GLFWwindow* win) {
	window = win;
	EntityManager::instance()->registerSystem(this);

	glfwSwapInterval(0);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	ResourceManager::instance()->loadResource(new Shader, "shader", "res/shader");
	shader = ResourceManager::instance()->getResource<Shader>("shader");
}

RenderSystem::~RenderSystem() { }

void RenderSystem::loop() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(unsigned int i = 0; i < entities.size(); i++) {
		Entity* entity = entities[i];
		Model* model = entity->model();

		if(!model->mesh->assigned) {
			loadModel(model);
		}

		glUseProgram(shader->program);

		glm::mat4 projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 1280.0f / 720.0f, 0.1f, 100.0f);
		glm::mat4 viewMatrix = glm::lookAt(
			glm::vec3(5.0f, 5.0f, 5.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		glm::mat4 modelMatrix = glm::mat4(1.0f);

		glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);
		glUniformMatrix4fv(shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, model->mesh->vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->mesh->ebo);
		glDrawElements(
			GL_TRIANGLES,
			model->mesh->vertexIndices.size(),
			GL_UNSIGNED_INT,
			0
		);
		glDisableVertexAttribArray(0);
	}

	glfwSwapBuffers(window);
}

void RenderSystem::loadModel(Model* model) {
	glGenVertexArrays(1, &model->mesh->vao);
	glBindVertexArray(model->mesh->vao);

	glGenBuffers(1, &model->mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, model->mesh->vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		model->mesh->vertices.size() * sizeof(glm::vec3),
		&model->mesh->vertices.front(),
		GL_STATIC_DRAW
	);

	glGenBuffers(1, &model->mesh->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->mesh->ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		model->mesh->vertexIndices.size() * sizeof(unsigned int),
		&model->mesh->vertexIndices.front(),
		GL_STATIC_DRAW
	);

	model->mesh->assigned = true;
}

void RenderSystem::attachEntity(Entity* entity) {
	if(entity->flags() & EntityFlags::RENDERABLE) {
		entities.push_back(entity);
	}
}