#pragma once

#include <set>

#include "GameBase.h"

class Rect;
class TextRenderer;

class Game : public GameBase {
public:
    std::set<Rect*> rects;
    GLuint count;

    Game();
    ~Game();
    void init(const GLFWvidmode* mode);
    void create();
    void processInput(const GLfloat dt);
    void update(const GLfloat dt);
    void changeBackground();
    void render() const;
    void checkMissed(const double mouseX, const double mouseY);
    void checkMouseClick(const double mouseX, const double mouseY);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};
