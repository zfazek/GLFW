#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

class Texture2D;

class Renderer {
public:
    Renderer(const Shader& shader);
    ~Renderer();
    void draw(const Texture2D& texture, const glm::vec3 position, const glm::vec3 size = glm::vec3(100, 100, 100), const GLfloat rotate = 0.0f, const glm::vec3 color = glm::vec3(1.0f));

private:
    Shader shader;
    GLuint VAO;

    void initRenderData();
};
