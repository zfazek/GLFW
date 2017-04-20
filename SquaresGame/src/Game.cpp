#include "Game.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Rect.h"
#include "ResourceManager.h"

Game::Game() : state(GameState::GAME_ACTIVE), keys{} {
    srand(std::time(0));
}

Game::~Game() {
    for (const auto& rect : rects) {
        delete rect;
    }
    delete textRenderer;
    ResourceManager::clear();
}

void Game::init() {
    Rect::init(width, height);
    textRenderer = new TextRenderer(width, height);
#ifdef __APPLE__
    textRenderer->load("ocraext.ttf", 48);
#else
    textRenderer->load("resources/ocraext.ttf", 48);
#endif
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
    } else if (state == GameState::GAME_WIN) {
        char text[128];
        snprintf(text, 128, "You clicked %d times.", count);
        textRenderer->renderText(text, 10, 10, 1);
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
        }
    }
}
