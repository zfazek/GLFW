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
    GLfloat lastFrameFPS = 0.0f;
    GLfloat deltaTimeFPS = 0.0f;
    long numFrame = 0;
    int fps = 0;

    while (!glfwWindowShouldClose(window)) {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        deltaTimeFPS = currentFrame - lastFrameFPS;
        lastFrame = currentFrame;
        clearBackground();
        render();
        glfwPollEvents();
        processInput(deltaTime);
        update(deltaTime);
        if (currentFrame - lastFrameFPS >= 1.0) {
            fps = numFrame/(currentFrame - lastFrameFPS);
            lastFrameFPS = currentFrame;
            numFrame = 0;
        }
        printFPS(fps);
        glfwSwapBuffers(window);
        ++numFrame;
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

void GameBase::printFPS(const int fps) const {}

void GameBase::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {}
void GameBase::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {}
void GameBase::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {}
