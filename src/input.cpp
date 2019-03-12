#include "input.h"

InputHandler* InputHandler::_instance = 0;
InputHandler::InputHandler() {}
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

void InputHandler::handleInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	for(KeyCallback& callback : keyBindings[key]) {
		if(action == GLFW_PRESS || action == GLFW_REPEAT) {
			callback(key, action, mods);
		}
	}
}

void InputHandler::handleCursor(GLFWwindow* window, double xpos, double ypos) {
	for(MouseCallback& callback : mouseBindings) {
		callback(xpos, ypos);
	}
}