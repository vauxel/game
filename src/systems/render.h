#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include "system.h"
#include "resources/shader.h"
#include "messages/input.h"

class RenderSystem : public System {
	private:
		GLFWwindow* window;
	public:
		Shader* shader;
		
		RenderSystem(GLFWwindow* win);
		~RenderSystem();

		virtual void attachEntity(Entity* entity);
		virtual void loop();
		virtual void handleMessage(MessageType type, Message* msg);
};

#endif