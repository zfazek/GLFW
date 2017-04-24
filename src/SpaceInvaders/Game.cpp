#include "Game.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Ship.h"
#include "Bullet.h"
#include "Droid.h"
#include "TextRenderer.h"

Game::Game() {
    srand(std::time(0));
}

Game::~Game() {
    delete ship;
    for (const auto& droid : droids) {
        delete droid;
    }
    for (const auto& bullet : bullets) {
        delete bullet;
    }
    delete textRenderer;
}

void Game::init(const GLFWvidmode* mode) {
    width = mode->width;
    height = mode->height;
    Ship::init(width, height);
    Bullet::init(width, height);
    Droid::init(width, height);
    textRenderer = new TextRenderer(width, height);
    lastBulletFrame = 0;
    create();
    state = GameState::GAME_ACTIVE;
    changeBackground();
    textRenderer->load("resources/ocraext.ttf", 48);
}

void Game::create() {
    count = 0;
    ship = new Ship(width, height);
    for (size_t i = 0; i < 50; i++) {
        Droid* droid = new Droid(1, width, height);
        droids.insert(droid);
    }
    state = GameState::GAME_ACTIVE;
}

void Game::update(const GLfloat dt) {
    if (state == GameState::GAME_ACTIVE) {
        ship->update(dt);
        for (const auto& droid : droids) {
            droid->update(dt);
        }
        std::set<Bullet*>::iterator it;
        for (it = bullets.begin(); it != bullets.end();) {
            (*it)->update(dt);
            if ((*it)->y < -100) {
                bullets.erase(it++);
            } else {
                ++it;
            }
        }
    }
}

void Game::processInput(const GLfloat dt) {
    if (keys[GLFW_KEY_LEFT]) {
        ship->x -= ship->speed * dt;
    }
    if (keys[GLFW_KEY_RIGHT]) {
        ship->x += ship->speed * dt;
    }
    if (keys[GLFW_KEY_SPACE]) {
        GLfloat currentFrame = glfwGetTime();
        if (currentFrame - lastBulletFrame > 1) {
            bullets.insert(new Bullet(width, height, ship->x + ship->side / 2, ship->side));
            lastBulletFrame = currentFrame;
        }
    }
}

void Game::changeBackground() {
    r = static_cast<GLfloat>(std::rand()) / RAND_MAX;
    g = static_cast<GLfloat>(std::rand()) / RAND_MAX;
    b = static_cast<GLfloat>(std::rand()) / RAND_MAX;
    //r = 0.1f;
    //g = 0.1f;
    //b = 0.1f;
}

void Game::render() const {
    if (state == GameState::GAME_ACTIVE) {
        ship->draw();
        for (const auto& droid : droids) {
            droid->draw();
        }
        for (const auto& bullet : bullets) {
            bullet->draw();
        }
    } else if (state == GameState::GAME_WIN) {
        char text[128];
        snprintf(text, 128, "You clicked %d times.", count);
        textRenderer->renderText(text, 10, 10, 1);
    }
}

void Game::checkMouseClick(const double mouseX, const double mouseY) {
    changeBackground();
}

void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        checkMouseClick(xpos, ypos);
    }
}
