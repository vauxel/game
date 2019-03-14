#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <sstream>
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
		glm::mat4 cameraMatrix;
		glm::mat4 modelMatrix;

		void updateCameraMatrix(Camera* cam);
		void updateModelMatrix(glm::vec3 pos, glm::quat rot);
		std::string getLightUniform(int index, const char* name);
		void updateLightingUniforms();
		void renderEntities();
	public:
		Shader* shader;
		Camera* camera;

		std::vector<Entity*> lights;
		
		RenderSystem(GLFWwindow* win);
		~RenderSystem();

		virtual void attachEntity(Entity* entity);
		virtual void loop();
		virtual void handleMessage(MessageType type, Message* msg);
		void moveLight1ToCamera();
		void moveLight2ToCamera();
};

#endif