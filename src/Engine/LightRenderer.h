#pragma once

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class LightRenderer {
public:
    LightRenderer(const Shader& shader);
    ~LightRenderer();
    void draw(const glm::vec3 position, const glm::vec3 size, const glm::vec3 rotate, const glm::vec3 color, const glm::mat4 projection, const glm::mat4 view);

private:
    Shader shader;
    GLuint VAO;

    void initRenderData();
};
