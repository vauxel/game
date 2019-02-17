#include "shader.h"

int Shader::load() {
	char vertShaderPath[strlen(resourcePath) + 5];
	char fragShaderPath[strlen(resourcePath) + 5];
	strcpy(vertShaderPath, resourcePath);
	strcpy(fragShaderPath, resourcePath);
	strcat(vertShaderPath, ".vert");
	strcat(fragShaderPath, ".frag");

	std::ifstream vertShaderFile(vertShaderPath), fragShaderFile(fragShaderPath);

	std::string vertexString(
		(std::istreambuf_iterator<char>(vertShaderFile)),
		(std::istreambuf_iterator<char>())
	);

	std::string fragmentString(
		(std::istreambuf_iterator<char>(fragShaderFile)),
		(std::istreambuf_iterator<char>())
	);

	const char* vertexSource = vertexString.c_str();
	const char* fragmentSource = fragmentString.c_str();

	int success;
	char infoLog[512];
	
	GLuint vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		LOG_ERROR("Vertex shader failed to compile: %s", infoLog);
	} else {
		LOG_DEBUG("Vertex shader successfully compiled");
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		LOG_ERROR("Fragment shader failed to compile: %s", infoLog);
	} else {
		LOG_DEBUG("Fragment shader successfully compiled");
	}

	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glBindFragDataLocation(program, 0, "outColor");
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		LOG_ERROR("Shader program failed to link: %s", infoLog);
	} else {
		LOG_DEBUG("Shader program successfully linked");
	}

	glDetachShader(program, vertex);
	glDetachShader(program, fragment);
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	LOG_DEBUG("Shader loaded: %s, %s", vertShaderPath, fragShaderPath);
	return 0;
}

void Shader::unload() {
	LOG_DEBUG("Shader unloaded: %s", resourcePath);
}

GLuint Shader::getUniformLocation(const char* uniform) {
	return glGetUniformLocation(program, uniform);
}