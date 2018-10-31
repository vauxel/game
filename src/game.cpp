#include <GLFW/glfw3.h>
#include "game.h"

Game::Game() {
    initGLFW();
}

Game::~Game() {
    if(window) {
        glfwTerminate();
    }
}

void Game::initGLFW() {
    /* Initialize the library */
    if(!glfwInit()) {
        return;
	}

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Test Game", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    initialized = true;
}

void Game::loop() {
    while(!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}