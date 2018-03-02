#include "Ship.h"

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Texture.h"

static char name[] = "ship";

Ship::Ship(const GLuint width, const GLuint height) : width(width), height(height) {
    speed = 500.0f;
    side = 100;
    x = std::rand() % (width - side);
    y = height - side;
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    color = glm::vec3(r, g, b);
    spriteRenderer = new SpriteRenderer(ResourceManager::getShader(name));
}

Ship::~Ship() {
    delete spriteRenderer;
}

void Ship::init(const GLuint width, const GLuint height) {
    ResourceManager::loadTexture("resources/ship.png", GL_TRUE, name);
    ResourceManager::loadShader("shaders/rect_vertex.glsl", "shaders/rect_fragment.glsl", nullptr, name);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader(name).use();
    ResourceManager::getShader(name).setInteger("image", 0);
    ResourceManager::getShader(name).setMatrix4fv("projection", projection);
}

void Ship::update(const GLfloat deltaTime) {
    if (x < -1 * side) {
        x = -side + 10;
    } else if (x > width) {
        x = width - 10;
    }
}

void Ship::draw() const {
    const Texture2D& texture = ResourceManager::getTexture(name);
    const glm::vec2 position = glm::vec2(x, y);
    const glm::vec2 size = glm::vec2(side, side);
    const GLfloat rotate = 0.0f;
    spriteRenderer->drawSprite(texture, position, size, rotate, color);
}
