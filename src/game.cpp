#include "game.h"
#include "entities/staticobject.h"

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

	resourceManager = ResourceManager::instance();
	entityManager = EntityManager::instance();

	renderSystem = new RenderSystem(window);

	glfwSetKeyCallback(window, handleInput);

	resourceManager->loadResource(new Mesh, "cube", "res/cube.obj");

	StaticObject* object = entityManager->spawn<StaticObject>();
	object->model()->init("cube", "");
}

void Game::initGLFW() {
	glfwSetErrorCallback(handleGLFWError);

	if(!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(1280, 720, "Game", NULL, NULL);
	if(!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	} else {
		std::cout << "GLFW window instantiated" << std::endl;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	} else {
		std::cout << "GLEW initialized" << std::endl;
	}

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