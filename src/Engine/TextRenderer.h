#pragma once

#include "Shader.h"

#include <GL/glew.h>

#include <map>

struct Character {
    GLuint textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

class TextRenderer {
public:
    std::map<GLchar, Character> characters;
    Shader textShader;
    TextRenderer(const GLuint width, const GLuint height);
    void load(const std::string& font, const GLuint fontSize);
    void renderText(const std::string& text, GLfloat x, const GLfloat y, const GLfloat scale, const glm::vec3 color = glm::vec3(1.0f));
private:
    GLuint VAO, VBO;
};
