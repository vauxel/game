#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "util/logger.h"
#include "resources/resource.h"
#include "systems/render.h"
#include "systems/control.h"
#include "input.h"
#include "entity.h"
#include "comp/render.h"
#include "comp/spatial.h"
#include "camera.h"

#define LOG_LEVEL LOG_LVL_DEBUG

class Game {
  private:
    static Game* _instance;
    bool running = false;
    ResourceManager* resourceManager;
    EntityManager* entityManager;
    InputHandler* inputHandler;
    RenderSystem* renderSystem;
    ControlSystem* controlSystem;
    Camera* camera;
    GLFWwindow* window;

    const unsigned int width = 1280;
    const unsigned int height = 720;

    Game();
    ~Game();

    void initGLFW();
    void quit();
    static void handleGLFWError(int error, const char* description);
    static void handleInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void handleCursor(GLFWwindow* window, double xpos, double ypos);
  public:
    bool initialized = false;

    static Game* instance();
    void init();
    void loop();
};
