#include "game.h"

Game* Game::_instance = 0;
Game::Game() {}

Game::~Game() {
	if (window) {
		glfwTerminate();
	}
}

Game* Game::instance() {
	if (_instance == 0) {
		_instance = new Game();
	}

	return _instance;
}

void Game::init() {
	initGLFW();

	resourceManager = ResourceManager::instance();
	entityManager = EntityManager::instance();

	inputHandler = InputHandler::instance();

	camera = new Camera(
		glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	renderSystem = new RenderSystem(window, camera);
	controlSystem = new ControlSystem(camera);

	glfwSetWindowUserPointer(window, this);

	glfwSetKeyCallback(window, handleInput);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, handleCursor);

	// resourceManager->loadResource(new Texture(), "checker", "res/checker.png");
	// resourceManager->loadResource(new Model(), "plane", "res/plane.obj");
	resourceManager->loadResource(new Texture(), "cube_texture", "res/cube_texture.png");
	// resourceManager->loadResource(new Model(), "cube", "res/cube_textured.obj");
	resourceManager->loadResource(new Model(), "cube", "res/cube.obj");

	// Entity* plane = new Entity();
	// plane->assign<Spatial>(glm::vec3(0.0f, 0.0f, 0.0f));
	// plane->assign<Render>("plane", "checker");

	Entity* cube = new Entity();
	cube->assign<Spatial>(glm::vec3(0.0f, 1.0f, 0.0f));
	cube->assign<Render>("cube", "cube_texture");

	Entity* light1 = new Entity();
	light1->assign<Spatial>(glm::vec3(0.0f, 3.0f, 0.0f));
	light1->assign<Light>(
		Light::Type::POINT,
		glm::vec3(2.0f, 2.0f, 2.0f),
		1.0f,
		0.05f
	);

	Entity* light2 = new Entity();
	light2->assign<Spatial>(glm::vec3(3.0f, 0.0f, 0.0f));
	light2->assign<Light>(
		Light::Type::SPOT,
		glm::vec3(1.0f, 1.0f, 1.0f),
		0.5f,
		0.0f,
		15.0f,
		glm::vec3(-1.0f, 0.0f, 0.0f)
	);

	Entity* light3 = new Entity();
	light3->assign<Spatial>(glm::vec3(0.0f, 1.0f, 5.0f));
	light3->assign<Light>(
		Light::Type::POINT,
		glm::vec3(2.0f, 0.0f, 0.0f),
		1.0f,
		0.0f
	);

	Entity* light4 = new Entity();
	light4->assign<Spatial>(glm::vec3(5.0f, 1.0f, 0.0f));
	light4->assign<Light>(
		Light::Type::POINT,
		glm::vec3(0.0f, 2.0f, 0.0f),
		1.0f,
		0.0f
	);

	Entity* light5 = new Entity();
	light5->assign<Spatial>(glm::vec3(0.0f, 1.0f, -5.0f));
	light5->assign<Light>(
		Light::Type::POINT,
		glm::vec3(0.0f, 0.0f, 2.0f),
		1.0f,
		0.0f
	);

	Entity* light6 = new Entity();
	light6->assign<Spatial>(glm::vec3(-5.0f, 1.0f, 0.0f));
	light6->assign<Light>(
		Light::Type::POINT,
		glm::vec3(2.0f, 0.0f, 2.0f),
		4.0f,
		0.0f
	);

	// entityManager->instantiate(plane);
	entityManager->instantiate(cube);
	entityManager->instantiate(light1);
	entityManager->instantiate(light2);
	entityManager->instantiate(light3);
	entityManager->instantiate(light4);
	entityManager->instantiate(light5);
	entityManager->instantiate(light6);

	inputHandler->addKeyBinding(GLFW_KEY_Q, std::bind(&Game::quit, this));
	inputHandler->addKeyBinding(GLFW_KEY_ESCAPE, std::bind(&Game::quit, this));

	LOG_INFO("Game initialized");
}

void Game::initGLFW() {
	glfwSetErrorCallback(handleGLFWError);

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(width, height, "Game", NULL, NULL);
	if (!window) {
		LOG_ERROR("GLFW window failed to be instantiated");
		glfwTerminate();
		exit(EXIT_FAILURE);
	} else {
		LOG_DEBUG("GLFW window instantiated");
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
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
		inputHandler->update();
		controlSystem->loop();
		renderSystem->loop();

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
