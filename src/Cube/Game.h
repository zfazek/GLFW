#pragma once

#include "GameBase.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

class Cube;
class CubeRenderer;
class LightRenderer;

class Game : public GameBase {
public:
    std::vector<Cube*> cubes;
    float lastX;
    float lastY;
    bool firstMouse;

    Game();
    ~Game();
    void init(GLFWwindow* window, const std::string& windowTitle, const GLuint width, const GLuint height);
    void create();
    void processInput(const GLfloat deltaTime);
    void update(const GLfloat deltaTime);
    void printFPS() const;
    void changeBackground();
    void render() const;
    void checkMouseClick(const double mouseX, const double mouseY);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

  private:
    CubeRenderer* cubeRenderer;
    LightRenderer* lightRenderer;
};
