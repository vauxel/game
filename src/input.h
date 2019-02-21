#ifndef _INPUT_H_
#define _INPUT_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "message.h"
#include "messages/input.h"

class Input {
	public:
		Input();
		~Input();

		static void handleInput(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif