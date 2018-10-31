#ifndef _GAME_H_
#define _GAME_H_

#include <GLFW/glfw3.h>

class Game {
	private:
		GLFWwindow* window;

		void initGLFW();
		void render();
		void update();
	public:
		bool initialized = false;

		Game();
		~Game();

		void loop();
};

#endif