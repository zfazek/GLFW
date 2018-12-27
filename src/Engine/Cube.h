#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class CubeRenderer;

class Cube {
    public:
        Cube(const GLuint x,
             const GLuint y,
             const GLuint z,
             glm::vec3 color);
        ~Cube();
        void update(const GLfloat deltaTime);
        void draw(CubeRenderer* cubeRenderer, const glm::mat4 projection, const glm::mat4 view,
                const glm::vec3 lightColor, glm::vec3 lightPos) const;
        static void init();
        static char name[];

    private:
        GLfloat side;
        GLfloat x, y, z;
        glm::vec3 color;
        GLuint width, height;
};
