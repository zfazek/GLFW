#include "Game.h"

#include <ctime>
#include <iostream>

#include "Rect.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

Game::Game() {
    srand(std::time(0));
}

Game::~Game() {
    for (const auto& rect : rects) {
        delete rect;
    }
    delete spriteRenderer;
    delete textRenderer;
}

void Game::init(GLFWwindow* window, const std::string& windowTitle, const GLuint width, const GLuint height) {
    this->window = window;
    this->windowTitle = windowTitle;
    this->width = width;
    this->height = height;
    Rect::init(width, height);
    create();
    changeBackground();
    spriteRenderer = new SpriteRenderer(ResourceManager::getShader(Rect::name));
    textRenderer = new TextRenderer(width, height);
    textRenderer->load("resources/ocraext.ttf", 48);
}

void Game::create() {
    count = 0;
    for (int i = 0; i < 100; i++) {
        Rect* rect = new Rect(width, height);
        rects.insert(rect);
    }
    state = GameState::GAME_ACTIVE;
}

void Game::update(const GLfloat deltaTime) {
    if (state == GameState::GAME_ACTIVE) {
        for (const auto& rect : rects) {
            rect->update(deltaTime);
        }
    }
}

void Game::processInput(const GLfloat deltaTime) {
}

void Game::changeBackground() {
    r = static_cast<GLfloat>(std::rand()) / RAND_MAX;
    g = static_cast<GLfloat>(std::rand()) / RAND_MAX;
    b = static_cast<GLfloat>(std::rand()) / RAND_MAX;
}

void Game::render() const {
    if (state == GameState::GAME_ACTIVE) {
        for (const auto& rect : rects) {
            rect->draw(spriteRenderer);
        }
        static char text[128];
        snprintf(text, 128, "%lu", rects.size());
        textRenderer->renderText(text, 10, 10, 1);
    } else if (state == GameState::GAME_WIN) {
        static char text[128];
        snprintf(text, 128, "You clicked %d times.", count);
        textRenderer->renderText(text, 10, 10, 1);
    }
}

void Game::checkMissed(const double mouseX, const double mouseY) {
    bool missed = true;
    for (auto it = rects.begin(); it != rects.end();) {
        if ((*it)->isInside(mouseX, mouseY)) {
            missed = false;
            delete *it;
            rects.erase(it++);
        } else {
            ++it;
        }
    }
    if (missed) {
        changeBackground();
        for (int i = 0; i < 4; i++) {
            rects.insert(new Rect(width, height));
        }
    }
}

void Game::checkMouseClick(const double mouseX, const double mouseY) {
    if (state == GameState::GAME_WIN) {
        create();
    } else if (state == GameState::GAME_ACTIVE) {
        count++;
        checkMissed(mouseX, mouseY);
        if (rects.size() == 0) {
            state = GameState::GAME_WIN;
        }
    }
}

void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        checkMouseClick(xpos, ypos);
    }
}
