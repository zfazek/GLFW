#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class CubeRenderer;

class Cube {
    public:
        Cube(const GLuint width, const GLuint height);
        Cube(const GLuint x,
             const GLuint y,
             const GLuint z,
             glm::vec3 color);
        ~Cube();
        void update(const GLfloat deltaTime);
        void draw(CubeRenderer* cubeRenderer, const glm::mat4 projection, const glm::mat4 view) const;
        static void init();
        static char name[];

    private:
        GLfloat side = 1.0f;
        GLfloat x, y, z, dx, dy;
        glm::vec3 color;
        GLuint width, height;
};
