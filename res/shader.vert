#version 460

uniform mat4 camera;
uniform mat4 model;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec3 fragPosition;
out vec2 fragUV;
out vec3 fragNormal;

void main() {
	fragPosition = vertexPosition;
	fragUV = vertexUV;
	fragNormal = vertexNormal;

	gl_Position = camera * model * vec4(vertexPosition, 1.0);
}