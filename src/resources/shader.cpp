#include "shader.h"

int Shader::load() {
	std::ifstream vertShaderFile(resourcePath + ".vert"), fragShaderFile(resourcePath + ".frag");

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
		std::cout << "Vertex shader failed to compile\n" << infoLog << std::endl;
	} else {
		std::cout << "Vertex shader successfully compiled" << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Fragment shader failed to compile\n" << infoLog << std::endl;
	} else {
		std::cout << "Fragment shader successfully compiled" << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glBindFragDataLocation(program, 0, "outColor");
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		std::cout << "Shader program failed to link\n" << infoLog << std::endl;
	} else {
		std::cout << "Shader program successfully linked" << std::endl;
	}

	glDetachShader(program, vertex);
	glDetachShader(program, fragment);
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return 0;
}

void Shader::unload() {
	
}

GLuint Shader::getUniformLocation(const char* uniform) {
	return glGetUniformLocation(program, uniform);
}