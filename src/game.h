#ifndef _GAME_H_
#define _GAME_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "util/logger.h"
#include "resources/resource.h"
#include "systems/render.h"
#include "entities/entity.h"

#define LOG_LEVEL LOG_LVL_DEBUG

class Game {
	private:
		static Game* _instance;
		bool running = false;
		ResourceManager* resourceManager;
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