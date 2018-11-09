#include "game.h"

Game* Game::_instance = 0;
Game::Game() {}

Game::~Game() {
	if(window) {
		glfwTerminate();
	}
}

Game* Game::instance() {
	if(_instance == 0) {
		_instance = new Game();
	}

	return _instance;
}

void Game::init() {
	initGLFW();
	entityManager = EntityManager::instance();
	renderSystem = new RenderSystem(window);
	glfwSetKeyCallback(window, handleInput);
}

void Game::initGLFW() {
	glfwSetErrorCallback(handleGLFWError);

	if(!glfwInit()) {
		return;
	}

	window = glfwCreateWindow(640, 480, "Test Game", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	initialized = true;
	running = !glfwWindowShouldClose(window);
}

void Game::loop() {
	while(running) {
		renderSystem->loop();
		
		glfwPollEvents();
		running = !glfwWindowShouldClose(window);
	}
}

void Game::handleInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void Game::handleGLFWError(int error, const char* description) {
	fprintf(stderr, "GLFW Error: %s\n", description);
}