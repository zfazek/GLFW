#include "Light.h"

#include "LightRenderer.h"
#include "ResourceManager.h"

char Light::name[] = "light";

Light::Light(const GLuint x_,
             const GLuint y_,
             const GLuint z_,
             const glm::vec3 color_) :
    side(0.5f),
    x(x_),
    y(y_),
    z(z_),
    color(color_) {
}

Light::~Light() {
}

void Light::init() {
    ResourceManager::loadShader("shaders/light_vertex.glsl", "shaders/light_fragment.glsl", nullptr, name);
}

void Light::update(const GLfloat deltaTime) {
}

void Light::draw(LightRenderer* lightRenderer, const glm::mat4 projection, const glm::mat4 view) const {
    const glm::vec3 position = glm::vec3(x, y, z);
    const glm::vec3 size = glm::vec3(side, side, side);
    glm::vec3 rotate(0.0f);
    lightRenderer->draw(position, size, rotate, color, projection, view);
}

glm::vec3 Light::getColor() const {
    return color;
}

glm::vec3 Light::getPosition() const {
    return glm::vec3(x, y, z);
}
