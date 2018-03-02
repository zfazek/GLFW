#include "Cube.h"

#include "CubeRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"

static char name[] = "cube";

Cube::Cube(const GLuint width, const GLuint height) : width(width), height(height) {
    side = 1.0f;
    x = 50 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    y = 0.0f;
    z = 0;//10 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r = static_cast<float>(std::rand()) / RAND_MAX;
    float g = static_cast<float>(std::rand()) / RAND_MAX;
    float b = static_cast<float>(std::rand()) / RAND_MAX;
    color = glm::vec3(r, g, b);
    cubeRenderer = new CubeRenderer(ResourceManager::getShader(name));
}

Cube::Cube(const GLuint width, const GLuint height,
        const GLuint x, const GLuint y, const GLuint z,
        const glm::vec3 color) :
                    side(1.0f),
                    x(x),
                    y(y),
                    z(z),
                    color(color) {
    cubeRenderer = new CubeRenderer(ResourceManager::getShader(name));
}

Cube::~Cube() {
    delete cubeRenderer;
}

void Cube::init(const GLuint width, const GLuint height) {
    ResourceManager::loadTexture("resources/block.png", GL_TRUE, name);
    ResourceManager::loadShader("shaders/3d_vertex.glsl", "shaders/3d_fragment.glsl", nullptr, name);
    ResourceManager::getShader(name).use();
    ResourceManager::getShader(name).setInteger("image", 0);
}

void Cube::update(const GLfloat deltaTime) {
    x += dx * deltaTime;
    y += dy * deltaTime;
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

void Cube::draw(glm::mat4 projection, glm::mat4 view) const {
    const Texture2D& texture = ResourceManager::getTexture(name);
    const glm::vec3 position = glm::vec3(x, y, z);
    const glm::vec3 size = glm::vec3(side, side, side);
    //glm::vec3 rotate(45.0f, -45.0f, 0.0f);
    glm::vec3 rotate;
    cubeRenderer->draw(texture, position, size, rotate, color,
            projection, view);
}
