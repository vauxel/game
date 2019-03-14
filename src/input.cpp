#include "input.h"

InputHandler* InputHandler::_instance = 0;

InputHandler::InputHandler() {
	for(unsigned int i = 0; i < KEY_COUNT; i++) {
		pressed[i] = false;
	}
}

InputHandler::~InputHandler() {}

InputHandler* InputHandler::instance() {
	if(_instance == 0) {
		_instance = new InputHandler();
	}

	return _instance;
}

void InputHandler::addKeyBinding(int key, const KeyCallback& callback) {
	keyBindings[key].push_back(callback);
	LOG_DEBUG("Registered callback for key %d", key);
}

void InputHandler::addMouseBinding(const MouseCallback& callback) {
	mouseBindings.push_back(callback);
	LOG_DEBUG("Registered callback for mouse");
}

void InputHandler::update() {
	glfwPollEvents();
}

bool InputHandler::isKeyPressed(int key) {
	return pressed[key];
}

void InputHandler::handleInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_UNKNOWN) {
		return;
	}

	if(action == GLFW_PRESS) {
		pressed[key] = true;
	} else if(action == GLFW_RELEASE) {
		pressed[key] = false;
	}

	for(KeyCallback& callback : keyBindings[key]) {
		callback(key, action, mods);
	}
}

void InputHandler::handleCursor(GLFWwindow* window, double xpos, double ypos) {
	for(MouseCallback& callback : mouseBindings) {
		callback(xpos, ypos);
	}
}