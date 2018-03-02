#pragma once

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Texture2D;

class CubeRenderer {
public:
    CubeRenderer(const Shader& shader);
    ~CubeRenderer();
    void draw(const Texture2D& texture, const glm::vec3 position, const glm::vec3 size, const glm::vec3 rotate, const glm::vec3 color,
            const glm::mat4 projection, const glm::mat4 view);

private:
    Shader shader;
    GLuint VAO;

    void initRenderData();
};
