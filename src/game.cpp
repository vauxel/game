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

	resourceManager = ResourceManager::instance();
	entityManager = EntityManager::instance();

	inputHandler = InputHandler::instance();

	renderSystem = new RenderSystem(window);

	glfwSetWindowUserPointer(window, this);

	glfwSetKeyCallback(window, handleInput);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, handleCursor);

	resourceManager->loadResource(new Texture(), "cube_texture", "res/cube_texture.png");
	resourceManager->loadResource(new Model(), "cube", "res/cube_textured.obj");

	Entity* cube = new Entity();
	cube->assign<Spatial>();
	cube->assign<Render>("cube", "cube_texture");
	entityManager->instantiate(cube);

	inputHandler->addKeyBinding(GLFW_KEY_Q, std::bind(&Game::quit, this));
	inputHandler->addKeyBinding(GLFW_KEY_ESCAPE, std::bind(&Game::quit, this));

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

	window = glfwCreateWindow(width, height, "Game", NULL, NULL);
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

void Game::quit() {
	glfwSetWindowShouldClose(window, 1);
}

void Game::handleGLFWError(int error, const char* description) {
	LOG_ERROR("GLFW Error: %s", description);
}

void Game::handleInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	InputHandler::instance()->handleInput(window, key, scancode, action, mods);
}
void Game::handleCursor(GLFWwindow* window, double xpos, double ypos) {
	InputHandler::instance()->handleCursor(window, xpos, ypos);
}