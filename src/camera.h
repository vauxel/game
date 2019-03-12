#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include "util/logger.h"

class Camera {
	public:
		Camera(
			glm::vec3 pos,
			glm::vec3 target,
			glm::vec3 up
		): pos(pos), target(target), up(up) {};

		glm::vec3& getPos();
		glm::vec3& getTarget();
		glm::vec3& getUp();

		void moveForward();
		void moveBackward();
		void moveLeft();
		void moveRight();
		void moveFromMouse(double xpos, double ypos);
	private:
		glm::vec3 pos;
		glm::vec3 target;
		glm::vec3 up;

		double yaw = 0.0;
		double pitch = 0.0;

		double mouseLastX = 0.0;
		double mouseLastY = 0.0;
		
		float mouseSens = 0.05f;
		float step = 0.5f;
};

#endif