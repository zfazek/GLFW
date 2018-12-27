#include "Cube.h"

#include "CubeRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"

char Cube::name[] = "cube";

Cube::Cube(const GLuint x_,
           const GLuint y_,
           const GLuint z_,
           const glm::vec3 color_) :
    side(1.0f),
    x(x_),
    y(y_),
    z(z_),
    color(color_) {
}

Cube::~Cube() {
}

void Cube::init() {
    ResourceManager::loadTexture("resources/block.png", GL_TRUE, name);
    ResourceManager::loadShader("shaders/3d_vertex.glsl", "shaders/3d_fragment.glsl", nullptr, name);
    ResourceManager::getShader(name).use();
    ResourceManager::getShader(name).setInteger("image", 0);
}

void Cube::update(const GLfloat deltaTime) {
}

void Cube::draw(CubeRenderer* cubeRenderer, const glm::mat4 projection, const glm::mat4 view, const glm::vec3 lightColor, glm::vec3 lightPos) const {
    const Texture2D& texture = ResourceManager::getTexture(name);
    const glm::vec3 position = glm::vec3(x, y, z);
    const glm::vec3 size = glm::vec3(side, side, side);
    glm::vec3 rotate(0.0f);
    cubeRenderer->draw(texture, position, size, rotate, color, projection, view, lightColor, lightPos);
}
