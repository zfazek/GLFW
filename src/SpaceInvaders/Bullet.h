#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class SpriteRenderer;

class Bullet {
    public:
        Bullet(const GLuint width, const GLuint height, const GLuint x, GLuint y);
        ~Bullet();
        void update(const GLfloat deltaTime);
        void draw() const;
        static void init(const GLuint width, const GLuint height);

        GLint x, y;
        GLfloat dx, dy;
        GLint side;
        glm::vec3 color;
        GLuint width, height;
        SpriteRenderer* spriteRenderer;
};
