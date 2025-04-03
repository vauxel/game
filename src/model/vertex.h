#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 normal;

	Vertex(const glm::vec3& posCoord, const glm::vec2& uvCoord, const glm::vec3& normalCoord) {
		pos = posCoord;
		uv = uvCoord;
		normal = normalCoord;
	}
};
