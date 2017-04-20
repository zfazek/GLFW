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

void Game::init(const GLFWvidmode* mode) {
	width = mode->width;
	height = mode->height;
	Rect::init(width, height);
	textRenderer = new TextRenderer(width, height);
	create();
	state = GameState::GAME_ACTIVE;
	changeBackground();

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

void Game::loop(GLFWwindow* window) {
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		processInput(deltaTime);
		update(deltaTime);
		clearBackground();
		render();
		glfwSwapBuffers(window);
	}
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

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
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

void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		checkMouseClick(xpos, ypos);
	}
}
