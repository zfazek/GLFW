#include "Game.h"

#include "Camera.h"
#include "Cube.h"
#include "CubeRenderer.h"
#include "Light.h"
#include "LightRenderer.h"
#include "ResourceManager.h"
#include "TextRenderer.h"

using std::string;
using std::rand;

Game::Game() {
}

Game::~Game() {
    for (const auto cube : cubes) {
        delete cube;
    }
    delete cubeRenderer;
    delete textRenderer;
    delete camera;
    delete light;
    delete lightRenderer;
}

void Game::init(GLFWwindow* window, const string& windowTitle, const GLuint width, const GLuint height) {
    this->window = window;
    this->windowTitle = windowTitle;
    this->width = width;
    this->height = height;
    lastX = width / 2.0f;
    lastY = height / 2.0f;
    firstMouse = true;
    Cube::init();
    Light::init();
    create();
    changeBackground();
    textRenderer = new TextRenderer(width, height);
    textRenderer->load("resources/ocraext.ttf", 48);
    cubeRenderer = new CubeRenderer(ResourceManager::getShader(Cube::name));
    lightRenderer = new LightRenderer(ResourceManager::getShader(Light::name));
}

void Game::create() {
    state = GameState::GAME_ACTIVE;
    for (GLuint x = 0; x < 50; x++) {
        for (GLuint z = 0; z < 50; z++) {
            const GLuint y = 0;
            float r = static_cast<float>(rand()) / RAND_MAX;
            float g = static_cast<float>(rand()) / RAND_MAX;
            float b = static_cast<float>(rand()) / RAND_MAX;
            glm::vec3 color = glm::vec3(r, g, b);
            Cube* cube = new Cube(x, y, z, color);
            cubes.push_back(cube);
        }
    }
    glm::vec3 color = glm::vec3(1.0f, 0.8f, 0.0f);
    light = new Light(20, 10, 20, color);
    glm::vec3 position = glm::vec3(0.0f, 10.0f, 0.0f);
    camera = new Camera(position);

}

void Game::update(const GLfloat deltaTime) {
    if (state == GameState::GAME_ACTIVE) {
        for (auto& cube : cubes) {
            cube->update(deltaTime);
        }
        light->update(deltaTime);
        projection = glm::perspective(glm::radians(camera->zoom),
                static_cast<float>(width) / static_cast<float>(height),
                0.1f, 100.0f);
        view = camera->getViewMatrix();
    }
}

void Game::printFPS() const {
    static char text[128];
    snprintf(text, 128, "FPS: %d", fps);
    textRenderer->renderText(text, 10, 45, 0.3f);
}

void Game::processInput(const GLfloat deltaTime) {
    if (state == GameState::GAME_ACTIVE) {
        if (keys[GLFW_KEY_W]) {
            camera->processKeyboard(CameraMovement::FORWARD, deltaTime);
        }
        if (keys[GLFW_KEY_S]) {
            camera->processKeyboard(CameraMovement::BACKWARD, deltaTime);
        }
        if (keys[GLFW_KEY_A]) {
            camera->processKeyboard(CameraMovement::LEFT, deltaTime);
        }
        if (keys[GLFW_KEY_D]) {
            camera->processKeyboard(CameraMovement::RIGHT, deltaTime);
        }
        if (keys[GLFW_KEY_SPACE]) {
            camera->processKeyboard(CameraMovement::UP, deltaTime);
        }
        if (keys[GLFW_KEY_LEFT_SHIFT]) {
            camera->processKeyboard(CameraMovement::DOWN, deltaTime);
        }
        if (keys[GLFW_KEY_F]) {
            toggleFullScreen();
        }
    }
}

void Game::changeBackground() {
    r = static_cast<GLfloat>(rand()) / RAND_MAX;
    g = static_cast<GLfloat>(rand()) / RAND_MAX;
    b = static_cast<GLfloat>(rand()) / RAND_MAX;
}

void Game::render() const {
    if (state == GameState::GAME_ACTIVE) {
        for (const auto cube : cubes) {
            cube->draw(cubeRenderer, projection, view, light->getColor(), light->getPosition());
        }
        light->draw(lightRenderer, projection, view);
        static char text[128];
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

void Game::checkMouseClick(const double /*mouseX*/, const double /*mouseY*/) {
}

    void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int /*mods*/) {
    if (action == GLFW_PRESS) {
        int cursorMode = glfwGetInputMode(window, GLFW_CURSOR);
        if (cursorMode == GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else if (cursorMode == GLFW_CURSOR_NORMAL) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        checkMouseClick(xpos, ypos);
    }
}

void Game::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
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
}

void Game::scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset) {
    camera->processMouseScroll(yoffset);
}
