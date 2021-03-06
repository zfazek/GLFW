#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class SpriteRenderer;

class Droid {
    public:
        Droid(const GLuint idx, const GLuint width, const GLuint height, const GLfloat x, const GLfloat y);
        ~Droid();
        void update(const GLfloat deltaTime);
        void draw() const;
        bool isInside(const double mouseX, const double mouseY) const;
        static void init(const GLuint width, const GLuint height);

        GLuint idx;
        GLfloat x, y, dx, dy;
        GLint side;
        glm::vec3 color;
        GLuint width, height;
        SpriteRenderer* spriteRenderer;
};
