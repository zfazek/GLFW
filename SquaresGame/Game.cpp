#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

SpriteRenderer *renderer;


Game::Game(GLuint width, GLuint height) : state(GAME_ACTIVE), keys(), width(width), height(height) {
}

Game::~Game() {
    delete renderer;
}

void Game::init() {
    ResourceManager::loadShader("shaders/vertex.glsl", "shaders/fragment.glsl", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").use().setInteger("image", 0);
    ResourceManager::getShader("sprite").setMatrix4("projection", projection);
    ResourceManager::loadTexture("resources/awesomeface.png", GL_TRUE, "face");
    renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
}

void Game::update(GLfloat dt) {

}

void Game::processInput(GLfloat dt) {

}

void Game::render() {
    const Texture2D& texture = ResourceManager::getTexture("face");
    const glm::vec2 position = glm::vec2(200, 200);
    glm::vec2 size = glm::vec2(80, 80);
    GLfloat rotate = 0.0f;
    glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);
    renderer->drawSprite(texture, position, size, rotate, color);
}
