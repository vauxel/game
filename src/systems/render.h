#pragma once

#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include "system.h"
#include "resources/shader.h"
#include "input.h"
#include "camera.h"
#include "entity.h"
#include "comp/render.h"

class RenderSystem : public System {
	private:
		GLFWwindow* window;
		Camera* camera;
		glm::mat4 cameraMatrix;
		glm::mat4 modelMatrix;

		void setCamera(Camera* cam);
		void updateCameraMatrix(Camera* cam);
		void updateModelMatrix(glm::vec3 pos, glm::quat rot);
		void updateLightingUniforms();
		void renderEntities();
	public:
		Shader* shader;
		std::vector<Entity*> lights;
		
		RenderSystem(GLFWwindow* win, Camera* cam);
		~RenderSystem();

		virtual void attachEntity(Entity* entity);
		virtual void loop();
		virtual void handleMessage(MessageType type, Message* msg);
		void moveLight1ToCamera();
		void moveLight2ToCamera();
};
