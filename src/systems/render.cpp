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

	MessageDispatcher::instance()->instance()->registerHandler(MessageType::INPUT, this);
}

RenderSystem::~RenderSystem() { }

void RenderSystem::loop() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(unsigned int i = 0; i < entities.size(); i++) {
		Entity* entity = entities[i];

		glUseProgram(shader->program);

		glm::mat4 projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 100.0f);
		glm::mat4 viewMatrix = glm::lookAt(
			glm::vec3(5.0f, 5.0f, 5.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		glm::mat4 modelMatrix = glm::mat4(1.0f);

		glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);
		glUniformMatrix4fv(shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);

		entity->render()->render();
	}

	glfwSwapBuffers(window);
}

void RenderSystem::attachEntity(Entity* entity) {
	if(entity->flags() & EntityFlags::RENDERABLE) {
		entities.push_back(entity);
	}
}

void RenderSystem::handleMessage(MessageType type, Message* msg) {
	if(type == MessageType::INPUT) {
		InputMsg* data = static_cast<InputMsg*>(msg);
		
		switch(data->keycode) {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
		}
	}
}