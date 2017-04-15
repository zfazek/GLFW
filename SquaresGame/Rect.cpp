#include "Rect.h"

#include <cmath>
#include <cstdlib>

#include "SpriteRenderer.h"
#include "ResourceManager.h"

Rect::Rect(const GLuint width, const GLuint height) : width(width), height(height) {
    const int maxSpeed = 100;
    side = std::rand() % 100 + 100;
    x = std::rand() % (width - side);
    y = std::rand() % (height - side);
    dx = 2 * (std::rand() % maxSpeed) - maxSpeed;
    dy = 2 * (std::rand() % maxSpeed) - maxSpeed;
    float r = static_cast<float>(std::rand()) / RAND_MAX;
    float g = static_cast<float>(std::rand()) / RAND_MAX;
    float b = static_cast<float>(std::rand()) / RAND_MAX;
    color = glm::vec3(r, g, b);
}

Rect::~Rect() {}

void Rect::update(const GLfloat dt) {
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

void Rect::draw(SpriteRenderer* renderer) const {
    const Texture2D& texture = ResourceManager::getTexture("face");
    const glm::vec2 position = glm::vec2(x, y);
    const glm::vec2 size = glm::vec2(side, side);
    const GLfloat rotate = 0.0f;
    renderer->drawSprite(texture, position, size, rotate, color);
}

bool Rect::isInside(double mouseX, double mouseY) const {
    return mouseX > x && mouseX < x + side && mouseY > y && mouseY < y + side;
}
