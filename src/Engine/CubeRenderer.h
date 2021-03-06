#pragma once

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CubeRenderer {
public:
    CubeRenderer();
    ~CubeRenderer();
    void draw(
            const glm::vec3 position,
            const glm::vec3 size,
            const glm::vec3 rotate,
            const glm::vec3 color,
            const glm::mat4 projection,
            const glm::mat4 view,
            const glm::vec3 lightColor,
            const glm::vec3 lightPos);

private:
    static char name[];
    Shader shader;
    GLuint VAO = 0;

    void init();
    void initRenderData();
};
