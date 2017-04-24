#include "Bullet.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Texture.h"

static char name[] = "bullet";

Bullet::Bullet(const GLuint width, const GLuint height, const GLuint x, const GLuint y) : width(width), height(height) {
    side = 40;
    this->x = x - side / 2;
    this->y = height - side - y;
    dx = 0.0f;
    dy = -100.0f;
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    color = glm::vec3(r, g, b);
    spriteRenderer = new SpriteRenderer(ResourceManager::getShader(name));
}

Bullet::~Bullet() {
    delete spriteRenderer;
}

void Bullet::init(const GLuint width, const GLuint height) {
    ResourceManager::loadTexture("resources/bullet.png", GL_TRUE, name);
    ResourceManager::loadShader("shaders/rect_vertex.glsl", "shaders/rect_fragment.glsl", nullptr, name);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader(name).use().setInteger("image", 0);
    ResourceManager::getShader(name).setMatrix4fv("projection", projection);
}

void Bullet::update(const GLfloat dt) {
    y += dy * dt;
}

void Bullet::draw() const {
    const Texture2D& texture = ResourceManager::getTexture(name);
    const glm::vec2 position = glm::vec2(x, y);
    const glm::vec2 size = glm::vec2(side, side);
    const GLfloat rotate = 0.0f;
    spriteRenderer->drawSprite(texture, position, size, rotate, color);
}
