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

	resourceManager->loadResource(new Texture(), "cube_texture", "res/cube_texture.png");
	resourceManager->loadResource(new Model(), "cube", "res/cube_textured.obj");

	StaticObject* object = entityManager->spawn<StaticObject>();
	object->render()->init("cube", "cube_texture");

	LOG_INFO("Game initialized");
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
		LOG_ERROR("GLFW window failed to be instantiated");
		glfwTerminate();
		exit(EXIT_FAILURE);
	} else {
		LOG_DEBUG("GLFW window instantiated");
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		LOG_ERROR("GLEW failed to be initialized");
		glfwTerminate();
		exit(EXIT_FAILURE);
	} else {
		LOG_DEBUG("GLEW initialized");
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
	LOG_ERROR("GLFW Error: %s", description);
}