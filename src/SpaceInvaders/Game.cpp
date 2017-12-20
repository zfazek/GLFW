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

void Game::init(GLFWwindow* window, const std::string& windowTitle, const GLint width, const GLint height) {
    this->window = window;
    this->windowTitle = windowTitle;
    this->width = width;
    this->height = height;
    Ship::init(width, height);
    Bullet::init(width, height);
    Droid::init(width, height);
    textRenderer = new TextRenderer(width, height);
    create();
    state = GameState::GAME_ACTIVE;
    changeBackground();
    textRenderer->load("resources/ocraext.ttf", 48);
    ship = new Ship(width, height);
}

void Game::create() {
    count = 0;
    bullets.clear();
    droids.clear();
    const GLfloat spanX = 100;
    const GLfloat spanY = 50;
    const size_t n_x = width / (spanX + 100);
    const size_t n_y = height / 2 / (spanY + 100);
    for (size_t i = 0; i < n_y; i++) {
        for (size_t j = 0; j < n_x; j++) {
            Droid* droid = new Droid(1, width, height, j * (spanX + 100), i * (spanY + 100));
            droids.insert(droid);
        }
    }
    lastBulletFrame = glfwGetTime();
    state = GameState::GAME_ACTIVE;
}

void Game::update(const GLfloat deltaTime) {
    if (state == GameState::GAME_ACTIVE) {
        ship->update(deltaTime);
        for (const auto& droid : droids) {
            droid->update(deltaTime);
        }
        std::set<Bullet*>::iterator itBullet;
        std::set<Droid*>::iterator itDroid;
        for (itBullet = bullets.begin(); itBullet != bullets.end();) {
            (*itBullet)->update(deltaTime);
            if ((*itBullet)->y < -100) {
                bullets.erase(itBullet++);
            } else {
                ++itBullet;
            }
        }
        bool collided = false;
        for (itBullet = bullets.begin(); itBullet != bullets.end();) {
            for (itDroid = droids.begin(); itDroid != droids.end();) {
                collided = isCollided(itBullet, itDroid);
                if (collided) {
                    droids.erase(itDroid);
                    itDroid = droids.end();
                } else {
                    ++itDroid;
                }
            }
            if (collided) {
                bullets.erase(itBullet++);
            } else {
                ++itBullet;
            }
        }
        if (droids.size() == 0) {
            state = GameState::GAME_WIN;
        }
    }
}

void Game::processInput(const GLfloat deltaTime) {
    if (state == GameState::GAME_ACTIVE) {
        if (keys[GLFW_KEY_LEFT]) {
            ship->x -= ship->speed * deltaTime;
        }
        if (keys[GLFW_KEY_RIGHT]) {
            ship->x += ship->speed * deltaTime;
        }
        if (keys[GLFW_KEY_SPACE]) {
            GLfloat currentFrame = glfwGetTime();
            if (currentFrame - lastBulletFrame > 1) {
                count++;
                bullets.insert(new Bullet(width, height, ship->x + ship->side / 2, ship->side));
                lastBulletFrame = currentFrame;
            }
        }
    } else if (state == GameState::GAME_WIN) {
        if (keys[GLFW_KEY_SPACE]) {
            create();
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
        ship->draw();
        for (const auto& droid : droids) {
            droid->draw();
        }
        for (const auto& bullet : bullets) {
            bullet->draw();
        }
    } else if (state == GameState::GAME_WIN) {
        char text[128];
        snprintf(text, 128, "You shot %d times.", count);
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

bool Game::isCollided(const std::set<Bullet*>::iterator itBullet, const std::set<Droid*>::iterator itDroid) const {
    const Bullet* b = *itBullet;
    const Droid* d = *itDroid;
    bool xCollision = false;
    bool yCollision = false;
    if (b->x > d->x && b->x < d->x + d->side) xCollision = true;
    if (b->x + b->side > d->x && b->x + b->side< d->x + d->side) xCollision = true;
    if (b->y > d->y && b->y < d->y + d->side) yCollision = true;
    if (b->y + b->side > d->y && b->y + b->side< d->y + d->side) yCollision = true;
    return xCollision && yCollision;

}
