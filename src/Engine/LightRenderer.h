#pragma once

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class LightRenderer {
public:
    LightRenderer();
    ~LightRenderer();
    void draw(const glm::vec3 position, const glm::vec3 size, const glm::vec3 rotate, const glm::vec3 color, const glm::mat4 projection, const glm::mat4 view);

private:
    static char name[];
    Shader shader;
    GLuint VAO = 0;

    void init();
    void initRenderData();
};
