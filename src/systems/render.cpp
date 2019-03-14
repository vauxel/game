#include "render.h"

RenderSystem::RenderSystem(GLFWwindow* win, Camera* cam) {
	window = win;
	camera = cam;

	EntityManager::instance()->registerSystem(this);

	glfwSwapInterval(1);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	ResourceManager::instance()->loadResource(new Shader, "shader", "res/shader");
	shader = ResourceManager::instance()->getResource<Shader>("shader");

	InputHandler::instance()->addKeyBinding(GLFW_KEY_1, std::bind(&RenderSystem::moveLight1ToCamera, this));
	InputHandler::instance()->addKeyBinding(GLFW_KEY_2, std::bind(&RenderSystem::moveLight2ToCamera, this));
}

RenderSystem::~RenderSystem() {}

void RenderSystem::setCamera(Camera* cam) {
	camera = cam;
}

void RenderSystem::updateCameraMatrix(Camera* cam) {
	glm::mat4 projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 100.0f);
	glm::mat4 viewMatrix = glm::lookAt(
		cam->getPos(),
		cam->getPos() + cam->getTarget(),
		cam->getUp()
	);

	cameraMatrix = projectionMatrix * viewMatrix;

	glUniformMatrix4fv(shader->getUniformLocation("camera"), 1, GL_FALSE, &cameraMatrix[0][0]);

	glUniform3fv(shader->getUniformLocation("cameraPosition"), 1, &cam->getPos()[0]);
}

void RenderSystem::updateModelMatrix(glm::vec3 pos, glm::quat rot) {
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, pos);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f));
	modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	//modelMatrix *= glm::mat4_cast(rot);

	glUniformMatrix4fv(shader->getUniformLocation("model"), 1, GL_FALSE, &modelMatrix[0][0]);
}

std::string RenderSystem::getLightUniform(int index, const char* name) {
	std::ostringstream stream;
	stream << "lights[" << index << "]." << name;
	return stream.str();
}

void RenderSystem::updateLightingUniforms() {
	glUniform1i(shader->getUniformLocation("numLights"), (int)lights.size());

	for(unsigned int i = 0; i < lights.size(); i++) {
		glUniform1i(
			shader->getUniformLocation(getLightUniform(i, "type").c_str()),
			lights[i]->get<Light>()->type
		);

		glUniform3fv(
			shader->getUniformLocation(getLightUniform(i, "position").c_str()),
			1,
			&lights[i]->get<Spatial>()->position[0]
		);

		glUniform3fv(
			shader->getUniformLocation(getLightUniform(i, "intensities").c_str()),
			1,
			&lights[i]->get<Light>()->intensities[0]
		);
		
		glUniform1f(
			shader->getUniformLocation(getLightUniform(i, "attenuation").c_str()),
			lights[i]->get<Light>()->attenuation
		);

		glUniform1f(
			shader->getUniformLocation(getLightUniform(i, "ambientCoefficient").c_str()),
			lights[i]->get<Light>()->ambientCoefficient
		);

		glUniform1f(
			shader->getUniformLocation(getLightUniform(i, "coneAngle").c_str()),
			lights[i]->get<Light>()->coneAngle
		);

		glUniform3fv(
			shader->getUniformLocation(getLightUniform(i, "coneDirection").c_str()),
			1,
			&lights[i]->get<Light>()->coneDirection[0]
		);
	}
}

void RenderSystem::renderEntities() {
	for(Entity* entity : entities) {
		updateModelMatrix(
			entity->get<Spatial>()->position,
			entity->get<Spatial>()->rotation
		);

		entity->get<Render>()->render();
	}
}

void RenderSystem::loop() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader->program);

	updateCameraMatrix(camera);
	updateLightingUniforms();
	renderEntities();

	glfwSwapBuffers(window);
}

void RenderSystem::attachEntity(Entity* entity) {
	if(entity->has<Render>() && entity->has<Spatial>()) {
		LOG_DEBUG("Attached render entity [id=%d]", entity->getId());
		entities.push_back(entity);
	}
	
	if(entity->has<Light>()) {
		LOG_DEBUG("Attached light entity [id=%d]", entity->getId());
		lights.push_back(entity);
	}
}

void RenderSystem::handleMessage(MessageType type, Message* msg) {}

void RenderSystem::moveLight1ToCamera() {
	glm::vec3 pos = camera->getPos();
	lights[0]->get<Spatial>()->position = pos;
	LOG_DEBUG("Set light 1 pos to [%f %f %f]", pos.x, pos.y, pos.z);
}

void RenderSystem::moveLight2ToCamera() {
	glm::vec3 pos = camera->getPos();
	glm::vec3 target = camera->getTarget();
	lights[1]->get<Spatial>()->position = pos;
	lights[1]->get<Light>()->coneDirection = target;
	LOG_DEBUG("Set light 2 pos to [%f %f %f] [%f %f %f]", pos.x, pos.y, pos.z, target.x, target.y, target.z);
}