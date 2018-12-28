#include "Cube.h"

#include "CubeRenderer.h"

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

void Cube::update(const GLfloat deltaTime) {
}

void Cube::draw(CubeRenderer* cubeRenderer, const glm::mat4 projection, const glm::mat4 view, const glm::vec3 lightColor, glm::vec3 lightPos) const {
    const glm::vec3 position = glm::vec3(x, y, z);
    const glm::vec3 size = glm::vec3(side, side, side);
    glm::vec3 rotate(0.0f);
    cubeRenderer->draw(position, size, rotate, color, projection, view, lightColor, lightPos);
}
