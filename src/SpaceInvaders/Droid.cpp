#include "Droid.h"

#include <cmath>
#include <cstdlib>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Texture.h"

static char name[] = "droid";

Droid::Droid(const GLuint idx, const GLuint width, const GLuint height) : idx(idx), width(width), height(height) {
    side = 100;
    x = (std::rand() % (width - side)) / side * side;
    y = (std::rand() % (height - 4 * side)) / side * side;
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    color = glm::vec3(r, g, b);
    spriteRenderer = new SpriteRenderer(ResourceManager::getShader(name));
}

Droid::~Droid() {
    delete spriteRenderer;
}

void Droid::init(const GLuint width, const GLuint height) {
    ResourceManager::loadTexture("resources/droid.png", GL_TRUE, name);
    ResourceManager::loadShader("shaders/rect_vertex.glsl", "shaders/rect_fragment.glsl", nullptr, name);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader(name).use().setInteger("image", 0);
    ResourceManager::getShader(name).setMatrix4fv("projection", projection);
}

void Droid::update(const GLfloat dt) {
}

void Droid::draw() const {
    const Texture2D& texture = ResourceManager::getTexture(name);
    const glm::vec2 position = glm::vec2(x, y);
    const glm::vec2 size = glm::vec2(side, side);
    const GLfloat rotate = 0.0f;
    spriteRenderer->drawSprite(texture, position, size, rotate, color);
}

bool Droid::isInside(const double mouseX, const double mouseY) const {
    return mouseX > x && mouseX < x + side && mouseY > y && mouseY < y + side;
}
