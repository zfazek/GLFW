#pragma once

#include "GameBase.h"

class TextRenderer;
class Cube;

class Game : public GameBase {
public:
    int count;
    Cube* cube;

    Game();
    ~Game();
    void init(const GLint width, const GLint height);
    void create();
    void processInput(const GLfloat dt);
    void update(const GLfloat dt);
    void changeBackground();
    void render() const;
    void checkMouseClick(const double mouseX, const double mouseY);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};
