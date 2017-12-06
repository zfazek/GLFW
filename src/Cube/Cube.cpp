#include "Cube.h"

#include <cmath>
#include <cstdlib>

#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture.h"

static char name[] = "cube";

Cube::Cube(const GLuint width, const GLuint height) : width(width), height(height) {
    const int maxSpeed = 100;
    side = std::rand() % 100 + 100;
    //x = std::rand() % (width - side);
    //y = std::rand() % (height - side);
    x = y = z = 0.0f;
    dx = 2 * (std::rand() % maxSpeed) - maxSpeed;
    dy = 2 * (std::rand() % maxSpeed) - maxSpeed;
    dz = 0.0f;
    float r = static_cast<float>(std::rand()) / RAND_MAX;
    float g = static_cast<float>(std::rand()) / RAND_MAX;
    float b = static_cast<float>(std::rand()) / RAND_MAX;
    color = glm::vec3(r, g, b);
    renderer = new Renderer(ResourceManager::getShader(name));
}

Cube::~Cube() {
    delete renderer;
}

void Cube::init(const GLuint width, const GLuint height) {
    ResourceManager::loadTexture("resources/block.png", GL_TRUE, name);
    ResourceManager::loadShader("shaders/3d_vertex.glsl", "shaders/3d_fragment.glsl", nullptr, name);
    //glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<GLfloat>(width) / static_cast<GLfloat>(height), 0.1f, 100.0f);
    glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    //ResourceManager::getShader(name).use();
    ResourceManager::getShader(name).setInteger("image", 0);
    ResourceManager::getShader(name).setMatrix4fv("projection", projection);
    ResourceManager::getShader(name).setMatrix4fv("view", view);
}

void Cube::update(const GLfloat dt) {
    x += dx * dt;
    y += dy * dt;
    if (x <= 0) {
        dx = std::abs(dx);
    } else if (x >= width - side) {
        dx = -std::abs(dx);
    }
    if (y <= 0) {
        dy = std::abs(dy);
    } else if (y > height - side) {
        dy = -std::abs(dy);
    }
}

void Cube::draw() const {
    const Texture2D& texture = ResourceManager::getTexture(name);
    const glm::vec3 position = glm::vec3(x, y, z);
    const glm::vec3 size = glm::vec3(side, side, side);
    const GLfloat rotate = 0.0f;
    renderer->draw(texture, position, size, rotate, color);
}
