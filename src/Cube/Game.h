#pragma once

#include "GameBase.h"

class TextRenderer;

class Game : public GameBase {
public:
    GLuint count;

    Game();
    ~Game();
    void init(const GLFWvidmode* mode);
    void create();
    void processInput(const GLfloat dt);
    void update(const GLfloat dt);
    void changeBackground();
    void render() const;
    void checkMouseClick(const double mouseX, const double mouseY);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};
