#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera;
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
    GLFWwindow* window;
    TextRenderer* textRenderer;
    Camera* camera;
    glm::mat4 projection;
    glm::mat4 view;

    GameBase();
    virtual ~GameBase();
    virtual void init(const GLint width, const GLint height) = 0;
    virtual void loop(GLFWwindow* window);
    virtual void processInput(const GLfloat deltaTime) = 0;
    virtual void update(const GLfloat deltaTime) = 0;
    virtual void updateTimers();
    virtual void calculateFPS();
    virtual void printFPS(const int fps) const;
    virtual void clearBackground() const;
    virtual void render() const = 0;
    virtual void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    virtual void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    virtual void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
    GLfloat currentTime;
    GLfloat deltaTime;
    GLfloat lastFrameTime;
    GLfloat lastFrameTimeFPS;
    GLfloat deltaTimeFPS;
    long numFrame;
    int fps;
};
