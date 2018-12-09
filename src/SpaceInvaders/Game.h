#pragma once

#include <set>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GameBase.h"

class Ship;
class Bullet;
class Droid;
class TextRenderer;

class Game : public GameBase {
public:
    Ship* ship;
    std::set<Bullet*> bullets;
    std::set<Droid*> droids;
    GLuint count;
    GLfloat lastBulletFrame;

    Game();
    ~Game();
    void init(GLFWwindow* window, const std::string& windowTitle, const GLuint width, const GLuint height);
    void create();
    void processInput(const GLfloat deltaTime);
    void update(const GLfloat deltaTime);
    void changeBackground();
    void render() const;
    void checkMouseClick(const double mouseX, const double mouseY);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    bool isCollided(const std::set<Bullet*>::iterator itBullet, const std::set<Droid*>::iterator itDroid) const;
};
