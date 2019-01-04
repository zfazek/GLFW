#pragma once

#include "GameBase.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CubesRenderer {
public:
    CubesRenderer();
    ~CubesRenderer();
    void draw(
            const Cubes& cubes,
            const glm::mat4 projection,
            const glm::mat4 view,
            const glm::vec3 lightColor,
            const glm::vec3 lightPos);

    static constexpr size_t MAX_NUMBER_OF_CUBES = 1000000;

private:
    static constexpr char name[] = "cubes";
    Shader shader;
    GLuint VAO = 0;
    GLuint colorsVBO;
    GLuint modelsVBO;
    glm::mat4 models[MAX_NUMBER_OF_CUBES];
    glm::vec3 colors[MAX_NUMBER_OF_CUBES];

    void init();
    void initRenderData();
};
