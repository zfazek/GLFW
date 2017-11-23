#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Renderer;

class Cube {
    public:
        Cube(const GLuint width, const GLuint height);
        ~Cube();
        void update(const GLfloat dt);
        void draw() const;
        static void init(const GLuint width, const GLuint height);

    private:
        GLfloat x, y, z, dx, dy, dz;
        GLuint side;
        glm::vec3 color;
        GLuint width, height;
        Renderer* renderer;
};
