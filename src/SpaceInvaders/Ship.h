#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class SpriteRenderer;

class Ship {
    public:
        Ship(const GLuint width, const GLuint height);
        ~Ship();
        void update(const GLfloat dt);
        void draw() const;
        static void init(const GLuint width, const GLuint height);

        GLfloat x, y;
        GLfloat speed;
        GLint side;
        glm::vec3 color;
        GLuint width, height;
        SpriteRenderer* spriteRenderer;
};
