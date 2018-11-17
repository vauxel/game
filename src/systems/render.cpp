#include "render.h"

RenderSystem::RenderSystem(GLFWwindow* win) {
	window = win;
	glfwSwapInterval(0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	EntityManager::instance()->registerSystem(this);
}

RenderSystem::~RenderSystem() { }

void RenderSystem::loop() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(unsigned int i = 0; i < entities.size(); i++) {
		Entity* entity = entities[i];
		Model* model = entity->model();

		// Render
	}

	glfwSwapBuffers(window);
	glFinish();
}

void RenderSystem::attachEntity(Entity* entity) {
	if(entity->flags() & EntityFlags::RENDERABLE) {
		entities.push_back(entity);
	}
}