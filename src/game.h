#ifndef _GAME_H_
#define _GAME_H_

#include <GLFW/glfw3.h>
#include <stdio.h>
#include "systems/render.h"
#include "entities/entity.h"

class Game {
	private:
		static Game* _instance;
		bool running = false;
		EntityManager* entityManager;
		RenderSystem* renderSystem;
		GLFWwindow* window;

		Game();
		~Game();

		void initGLFW();
		static void handleInput(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void handleGLFWError(int error, const char* description);
	public:
		bool initialized = false;

		static Game* instance();
		void init();
		void loop();
};

#endif