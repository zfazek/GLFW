#include "Game.h"

GameBase* game = new Game();
const GLint width = 800;
const GLint height = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    game->framebuffer_size_callback(window, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    game->key_callback(window, key, scancode, action, mode);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    game->mouse_button_callback(window, button, action, mods);
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    game->cursor_pos_callback(window, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    game->scroll_callback(window, xoffset, yoffset);
}

int main(int argc, char *argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    const std::string windowTitle = "Cube";
    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glViewport(0, 0, width, height);
//    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    game->init(window, windowTitle, width, height);
    game->loop();

    delete game;
    glfwTerminate();
    return 0;
}
