#pragma once

#include <set>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Rect;

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
public:
    GameState state;
    GLboolean keys[1024];
    GLuint width, height;
    GLuint count;
    std::set<Rect*> rects;

    Game(GLuint width, GLuint height);
    ~Game();

    void init();
    void create();
    void processInput(GLfloat dt);
    void update(GLfloat dt);
    void render();
    void checkMouseClick(double mouseX, double mouseY);
};
