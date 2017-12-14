#include "Game.h"

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
    delete cube;
    delete textRenderer;
}

void Game::init(const GLint width, const GLint height) {
    this->width = width;
    this->height = height;
    Cube::init(width, height);
    create();
    changeBackground();
    textRenderer = new TextRenderer(width, height);
    textRenderer->load("resources/ocraext.ttf", 48);
}

void Game::create() {
    state = GameState::GAME_ACTIVE;
    cube = new Cube(width, height);
}

void Game::update(const GLfloat dt) {
    if (state == GameState::GAME_ACTIVE) {
        //cube->update(dt);
    }
}

void Game::processInput(const GLfloat dt) {
}

void Game::changeBackground() {
    r = static_cast<GLfloat>(std::rand()) / RAND_MAX;
    g = static_cast<GLfloat>(std::rand()) / RAND_MAX;
    b = static_cast<GLfloat>(std::rand()) / RAND_MAX;
}

void Game::render() const {
    if (state == GameState::GAME_ACTIVE) {
        cube->draw();
        char text[128];
        snprintf(text, 128, "Text is working");
        textRenderer->renderText(text, 10, 10, 0.5f);
    } else if (state == GameState::GAME_WIN) {
    }
}

void Game::checkMouseClick(const double mouseX, const double mouseY) {
}

void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        checkMouseClick(xpos, ypos);
    }
}
