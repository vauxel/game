#ifndef _INPUT_H_
#define _INPUT_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>
#include <map>
#include "util/logger.h"

class InputHandler {
	using KeyCallback = std::function<void(int, int, int)>;
	using MouseCallback = std::function<void(double, double)>;

	private:
		static InputHandler* _instance;
		std::map<int, std::vector<KeyCallback>> keyBindings;
		std::vector<MouseCallback> mouseBindings;

		InputHandler();
		~InputHandler();
	public:
		static InputHandler* instance();
		void addKeyBinding(int key, const KeyCallback& callback);
		void addMouseBinding(const MouseCallback& callback);
		void handleInput(GLFWwindow* window, int key, int scancode, int action, int mods);
		void handleCursor(GLFWwindow* window, double xpos, double ypos);
};

#endif