#include "render.h"

RenderSystem::RenderSystem(GLFWwindow* win) {
	window = win;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	EntityManager::instance()->registerSystem(this);
}

RenderSystem::~RenderSystem() { }

void RenderSystem::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}

void RenderSystem::loop() {
	render();
}

void RenderSystem::attachEntity(Entity* entity) {
	entities.push_back(entity);
}