#pragma once

#include <set>

#include <GL/glew.h>

#include "TextRenderer.h"

class Rect;

enum class GameState {
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
        GLfloat r, g, b;
        std::set<Rect*> rects;
        TextRenderer* textRenderer;

        Game();
        ~Game();

        void init();
        void create();
        void processInput(const GLfloat dt);
        void update(const GLfloat dt);
        void clearBackground() const;
        void changeBackground();
        void render() const;
        void checkMouseClick(const double mouseX, const double mouseY);
};
