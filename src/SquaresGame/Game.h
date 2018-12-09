#pragma once

#include <set>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GameBase.h"

class SpriteRenderer;
class Rect;

class Game : public GameBase {
public:
    std::set<Rect*> rects;
    int count;

    Game();
    ~Game();
    void init(GLFWwindow* window, const std::string& windowTitle, const GLuint width, const GLuint height);
    void create();
    void processInput(const GLfloat deltaTime);
    void update(const GLfloat deltaTime);
    void changeBackground();
    void render() const;
    void checkMissed(const double mouseX, const double mouseY);
    void checkMouseClick(const double mouseX, const double mouseY);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

  private:
    SpriteRenderer* spriteRenderer;
};
