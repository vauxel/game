#include "camera.h"

glm::vec3& Camera::getPos() {
	return pos;
}

glm::vec3& Camera::getTarget() {
	return target;
}

glm::vec3& Camera::getUp() {
	return up;
}

void Camera::moveForward() {
	pos += target * step;
}

void Camera::moveBackward() {
	pos -= target * step;
}

void Camera::moveLeft() {
	pos -= glm::normalize(glm::cross(target, up)) * step;
}

void Camera::moveRight() {
	pos += glm::normalize(glm::cross(target, up)) * step;
}

void Camera::moveFromMouse(double xpos, double ypos) {
	if (mouseLastX == 0.0 || mouseLastY == 0.0) {
		mouseLastX = xpos;
		mouseLastY = ypos;
	}

	double xoffset = (xpos - mouseLastX) * mouseSens;
	double yoffset = (mouseLastY - ypos) * mouseSens;
	mouseLastX = xpos;
	mouseLastY = ypos;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}

	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	target.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	target.y = sin(glm::radians(pitch));
	target.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	target = glm::normalize(target);
}