#include "Game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Rect.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

SpriteRenderer* renderer;

Game::Game(GLuint width, GLuint height) : state(GAME_ACTIVE), keys(), width(width), height(height) {
    srand(std::time(0));
}

Game::~Game() {
    delete renderer;
}

void Game::init() {
#ifdef __APPLE__
    ResourceManager::loadTexture("/Users/zfazek/git/GLFW/SquaresGame/resources/block.png", GL_TRUE, "face");
    ResourceManager::loadShader("/Users/zfazek/git/GLFW/SquaresGame/shaders/vertex.glsl", "/Users/zfazek/git/GLFW/SquaresGame/shaders/fragment.glsl", nullptr, "sprite");
#else
    ResourceManager::loadTexture("resources/block.png", GL_TRUE, "face");
    ResourceManager::loadShader("shaders/vertex.glsl", "shaders/fragment.glsl", nullptr, "sprite");
#endif
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").use().setInteger("image", 0);
    ResourceManager::getShader("sprite").setMatrix4("projection", projection);
    renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
}

void Game::create() {
    count = 0;
    for (int i = 0; i < 100; i++) {
        Rect* rect = new Rect(width, height);
        rects.insert(rect);
    }
}

void Game::update(GLfloat dt) {
    for (const auto& rect : rects) {
        rect->update(dt);
    }
}

void Game::processInput(GLfloat dt) {
}

void Game::render() {
    for (const auto& rect : rects) {
        rect->draw(renderer);
    }
}

void Game::checkMouseClick(double mouseX, double mouseY) {
    if (rects.size() == 0) {
        create();
    } else {
        bool missed = true;
        count++;
		for (auto it = rects.begin(); it != rects.end();) {
            if ((*it)->isInside(mouseX, mouseY)) {
                missed = false;
                rects.erase(it++);
			} else {
				++it;
			}
        }
        if (missed) {
            for (int i = 0; i < 4; i++) {
                rects.insert(new Rect(width, height));
            }
        }
        if (rects.size() == 0) {
            std::cout << "You clicked " << count << " times." << std::endl;
        }
    }
}
