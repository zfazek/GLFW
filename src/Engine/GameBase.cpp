#include "GameBase.h"

#include "ResourceManager.h"

GameBase::GameBase() : keys{} {
    currentTime = 0.0f;
    deltaTime = 0.0f;
    lastFrameTime = 0.0f;
    lastFrameTimeFPS = 0.0f;
    deltaTimeFPS = 0.0f;
    numFrame = 0;
    fps = 0;
}

GameBase::~GameBase() {
    ResourceManager::clear();
}

void GameBase::clearBackground() const {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameBase::loop() {

    while (!glfwWindowShouldClose(window)) {
        clearBackground();
        render();
        glfwPollEvents();
        updateTimers();
        processInput(deltaTime);
        update(deltaTime);
        calculateFPS();
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

void GameBase::updateTimers() {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrameTime;
    deltaTimeFPS = currentTime - lastFrameTimeFPS;
    lastFrameTime = currentTime;
}

void GameBase::calculateFPS() {
    if (currentTime - lastFrameTimeFPS >= 1.0) {
        fps = numFrame/(currentTime - lastFrameTimeFPS);
        lastFrameTimeFPS = currentTime;
        numFrame = 0;
    }
}

void GameBase::toggleFullScreen() {
    if (fullScreen) {

    } else {
    }
    fullScreen = !fullScreen;
}

void GameBase::printFPS(const int fps) const {}

void GameBase::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {}
void GameBase::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {}
void GameBase::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {}
