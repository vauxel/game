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
	LOG_DEBUG("Camera: FORWARD");
	pos += target * step;
}

void Camera::moveBackward() {
	LOG_DEBUG("Camera: BACKWARD");
	pos -= target * step;
}

void Camera::moveLeft() {
	LOG_DEBUG("Camera: LEFT");
	pos -= glm::normalize(glm::cross(target, up)) * step;
}

void Camera::moveRight() {
	LOG_DEBUG("Camera: RIGHT");
	pos += glm::normalize(glm::cross(target, up)) * step;
}

void Camera::moveFromMouse(double xpos, double ypos) {
	if(mouseLastX == 0.0 || mouseLastY == 0.0) {
		mouseLastX = xpos;
		mouseLastY = ypos;
	}

	double xoffset = (xpos - mouseLastX) * mouseSens;
	double yoffset = (mouseLastY - ypos) * mouseSens;
	mouseLastX = xpos;
	mouseLastY = ypos;

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f) {
		pitch = 89.0f;
	}

	if(pitch < -89.0f) {
		pitch = -89.0f;
	}

	target.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	target.y = sin(glm::radians(pitch));
	target.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	target = glm::normalize(target);

	LOG_DEBUG("Pos: %f %f %f", pos.x, pos.y, pos.z);
	LOG_DEBUG("Target: %f %f %f", target.x, target.y, target.z);
	LOG_DEBUG("Up: %f %f %f", up.x, up.y, up.z);
}