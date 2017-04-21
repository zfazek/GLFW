#include "GameBase.h"

#include <GL/glew.h>

#include "ResourceManager.h"

GameBase::GameBase() {
}

GameBase::~GameBase() {
    ResourceManager::clear();
}

void GameBase::clearBackground() const {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GameBase::loop(GLFWwindow* window) {
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        processInput(deltaTime);
        update(deltaTime);
        clearBackground();
        render();
        glfwSwapBuffers(window);
    }
}

void GameBase::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keys[key] = GL_TRUE;
        }
        else if (action == GLFW_RELEASE) {
            keys[key] = GL_FALSE;
        }
    }
}



