#include "GameBase.h"

#include "ResourceManager.h"

GameBase::GameBase() : keys{}{
}

GameBase::~GameBase() {
    ResourceManager::clear();
}

void GameBase::clearBackground() const {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        clearBackground();
        update(deltaTime);
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

void GameBase::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void GameBase::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {}
void GameBase::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {}
void GameBase::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {}
