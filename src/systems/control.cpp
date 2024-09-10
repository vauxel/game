#include "control.h"

ControlSystem::ControlSystem(Camera* cam) {
	camera = cam;
	EntityManager::instance()->registerSystem(this);

	InputHandler::instance()->addMouseBinding(std::bind(
		&Camera::moveFromMouse,
		camera,
		std::placeholders::_1,
		std::placeholders::_2
	));
}

ControlSystem::~ControlSystem() {}

void ControlSystem::loop() {
	if (cameraControl) {
		if (InputHandler::instance()->isKeyPressed(GLFW_KEY_W)) {
			camera->moveForward();
		}

		if (InputHandler::instance()->isKeyPressed(GLFW_KEY_S)) {
			camera->moveBackward();
		}

		if (InputHandler::instance()->isKeyPressed(GLFW_KEY_A)) {
			camera->moveLeft();
		}

		if (InputHandler::instance()->isKeyPressed(GLFW_KEY_D)) {
			camera->moveRight();
		}
	}
}

void ControlSystem::attachEntity(Entity* entity) {}
void ControlSystem::handleMessage(MessageType type, Message* msg) {}