#include "input.h"

Input::Input() {

}

Input::~Input() {

}

void Input::handleInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(action == GLFW_PRESS) {
		MessageDispatcher::instance()->dispatch(
			MessageType::INPUT,
			new InputMsg{key}
		);
	}
}