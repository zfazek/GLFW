#include "Game.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Cube.h"
#include "TextRenderer.h"

Game::Game() {
    srand(std::time(0));
}

Game::~Game() {
    for (const auto cube : cubes) {
        delete cube;
    }
    delete textRenderer;
    delete camera;
}

void Game::init(const GLint width, const GLint height) {
    this->width = width;
    this->height = height;
    lastX = width / 2.0f;
    lastY = height / 2.0f;
    firstMouse = true;
    Cube::init(width, height);
    create();
    changeBackground();
    textRenderer = new TextRenderer(width, height);
    textRenderer->load("resources/ocraext.ttf", 48);
}

void Game::create() {
    state = GameState::GAME_ACTIVE;
    for (int x = 0; x < 50; x++) {
        for (int z = 0; z < 50; z++) {
            const GLuint y = 0;
            float r = static_cast<float>(std::rand()) / RAND_MAX;
            float g = static_cast<float>(std::rand()) / RAND_MAX;
            float b = static_cast<float>(std::rand()) / RAND_MAX;
            glm::vec3 color = glm::vec3(r, g, b);
            Cube* cube = new Cube(width, height, x, y, z, color);
            cubes.push_back(cube);
        }
    }
    glm::vec3 position = glm::vec3(0.0f, 10.0f, 0.0f);
    camera = new Camera(position);
}

void Game::update(const GLfloat deltaTime) {
    if (state == GameState::GAME_ACTIVE) {
        //cube->update(dt);
        projection = glm::perspective(glm::radians(camera->zoom),
                static_cast<GLfloat>(width) / static_cast<GLfloat>(height),
                0.1f, 100.0f);
        view = camera->getViewMatrix();
        char text[128];
        snprintf(text, 128, "FPS: %d", (int)(60/deltaTime));
        textRenderer->renderText(text, 10, 45, 0.3f);
    }
}

void Game::processInput(const GLfloat deltaTime) {
    if (state == GameState::GAME_ACTIVE) {
        if (keys[GLFW_KEY_W]) {
            camera->processKeyboard(FORWARD, deltaTime);
        }
        if (keys[GLFW_KEY_S]) {
            camera->processKeyboard(BACKWARD, deltaTime);
        }
        if (keys[GLFW_KEY_A]) {
            camera->processKeyboard(LEFT, deltaTime);
        }
        if (keys[GLFW_KEY_D]) {
            camera->processKeyboard(RIGHT, deltaTime);
        }
        if (keys[GLFW_KEY_SPACE]) {
            camera->processKeyboard(UP, deltaTime);
        }
        if (keys[GLFW_KEY_LEFT_SHIFT]) {
            camera->processKeyboard(DOWN, deltaTime);
        }
    }
}

void Game::changeBackground() {
    r = static_cast<GLfloat>(std::rand()) / RAND_MAX;
    g = static_cast<GLfloat>(std::rand()) / RAND_MAX;
    b = static_cast<GLfloat>(std::rand()) / RAND_MAX;
}

void Game::render() const {
    if (state == GameState::GAME_ACTIVE) {
        for (const auto cube : cubes) {
            cube->draw(projection, view);
        }
        char text[128];
        snprintf(text, 128, "Pos: (%.1f, %.1f, %.1f)",
                camera->position.x,
                camera->position.y,
                camera->position.z);
        textRenderer->renderText(text, 10, 10, 0.3f);
        snprintf(text, 128, "Front: (%.1f, %.1f, %.1f)",
                camera->front.x,
                camera->front.y,
                camera->front.z);
        textRenderer->renderText(text, 10, 30, 0.3f);
    } else if (state == GameState::GAME_WIN) {
    }
}

void Game::checkMouseClick(const double mouseX, const double mouseY) {
}

void Game::mouse_button_callback(GLFWwindow* window, int button, int action,
        int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        checkMouseClick(xpos, ypos);
    }
}

void Game::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(xoffset, yoffset);
}

void Game::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera->processMouseScroll(yoffset);
}
