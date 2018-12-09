#include "Rect.h"

#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"

std::string Rect::name = "rect";

Rect::Rect(const GLuint width_, const GLuint height_) : width(width_), height(height_) {
    const int maxSpeed = 100;
    side = std::rand() % height / 15 + height / 15;
    x = std::rand() % (width - side);
    y = std::rand() % (height - side);
    dx = 2 * (std::rand() % maxSpeed) - maxSpeed;
    dy = 2 * (std::rand() % maxSpeed) - maxSpeed;
    float r = static_cast<float>(std::rand()) / RAND_MAX;
    float g = static_cast<float>(std::rand()) / RAND_MAX;
    float b = static_cast<float>(std::rand()) / RAND_MAX;
    color = glm::vec3(r, g, b);
}

Rect::~Rect() {
}

void Rect::init(const GLuint width, const GLuint height) {
    ResourceManager::loadTexture("resources/block.png", GL_TRUE, name);
    ResourceManager::loadShader("shaders/rect_vertex.glsl", "shaders/rect_fragment.glsl", nullptr, name);
    glm::mat4 projection = glm::ortho<float>(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader(name).use();
    ResourceManager::getShader(name).setInteger("image", 0);
    ResourceManager::getShader(name).setMatrix4fv("projection", projection);
}

void Rect::update(const GLfloat deltaTime) {
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

void Rect::draw(SpriteRenderer* spriteRenderer) const {
    const Texture2D& texture = ResourceManager::getTexture(name);
    const glm::vec2 position = glm::vec2(x, y);
    const glm::vec2 size = glm::vec2(side, side);
    const GLfloat rotate = 0.0f;
    spriteRenderer->drawSprite(texture, position, size, rotate, color);
}

bool Rect::isInside(const double mouseX, const double mouseY) const {
    return mouseX > x && mouseX < x + side && mouseY > y && mouseY < y + side;
}
