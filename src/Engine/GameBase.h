#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TextRenderer;

enum class GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class GameBase {
public:
    GameState state;
    GLboolean keys[1024];
    GLuint width, height;
    GLfloat r, g, b;
    TextRenderer* textRenderer;

    GameBase();
    virtual ~GameBase();
    virtual void init(const GLint width, const GLint height) = 0;
    virtual void loop(GLFWwindow* window);
    virtual void processInput(const GLfloat dt) = 0;
    virtual void update(const GLfloat dt) = 0;
    virtual void clearBackground() const;
    virtual void render() const = 0;
    virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) = 0;


};
