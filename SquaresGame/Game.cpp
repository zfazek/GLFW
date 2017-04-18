#include "Game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Rect.h"
#include "ResourceManager.h"

Game::Game(const GLuint width, const GLuint height) : state(GameState::GAME_ACTIVE), keys(), width(width), height(height) {
    srand(std::time(0));
}

Game::~Game() {
    for (const auto& rect : rects) {
        delete rect;
    }
}

void Game::init() {
    Rect::init(width, height);
}

void Game::create() {
    count = 0;
    for (int i = 0; i < 100; i++) {
        Rect* rect = new Rect(width, height);
        rects.insert(rect);
    }
    state = GameState::GAME_ACTIVE;
}

void Game::update(const GLfloat dt) {
    if (state == GameState::GAME_ACTIVE) {
        for (const auto& rect : rects) {
            rect->update(dt);
        }
    }
}

void Game::processInput(const GLfloat dt) {
}

void Game::changeBackground() {
    r = static_cast<GLfloat>(std::rand()) / RAND_MAX;
    g = static_cast<GLfloat>(std::rand()) / RAND_MAX;
    b = static_cast<GLfloat>(std::rand()) / RAND_MAX;
}

void Game::clearBackground() const {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::render() const {
    if (state == GameState::GAME_ACTIVE) {
        for (const auto& rect : rects) {
            rect->draw();
        }
    }
}

void Game::checkMouseClick(const double mouseX, const double mouseY) {
    if (state == GameState::GAME_WIN) {
        create();
    } else if (state == GameState::GAME_ACTIVE) {
        bool missed = true;
        count++;
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
        if (rects.size() == 0) {
            state = GameState::GAME_WIN;
            std::cout << "You clicked " << count << " times." << std::endl;
        }
    }
}
