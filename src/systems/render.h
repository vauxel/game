#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "data/vectors.h"
#include "system.h"

class RenderSystem : public System {
	private:
		GLFWwindow* window;
	public:
		RenderSystem(GLFWwindow* win);
		~RenderSystem();

		virtual void attachEntity(Entity* entity);
        virtual void loop();
};

#endif