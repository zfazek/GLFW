#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>

class Camera;
class Light;
class TextRenderer;

enum class GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class GameBase {
public:
    GameBase();
    virtual ~GameBase();
    virtual void init(GLFWwindow* window, const std::string& windowTitle, const GLuint width, const GLuint height) = 0;
    void toggleFullScreen();
    void loop();
    virtual void processInput(const GLfloat deltaTime) = 0;
    virtual void update(const GLfloat deltaTime) = 0;
    void updateTimers();
    void calculateFPS();
    virtual void printFPS() const;
    void clearBackground() const;
    virtual void render() const = 0;
    virtual void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    virtual void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    virtual void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

protected:
    GameState state;
    GLboolean keys[1024];
    GLuint width, height;
    GLfloat r, g, b;
    GLFWwindow* window;
    TextRenderer* textRenderer;
    Camera* camera;
    Light* light;
    glm::mat4 projection;
    glm::mat4 view;
    std::string windowTitle;
    bool fullScreen;
    bool cursorDisabled;
    int fps;

private:
    GLfloat currentTime;
    GLfloat deltaTime;
    GLfloat lastFrameTime;
    GLfloat lastFrameTimeFPS;
    long numFrame;
};
