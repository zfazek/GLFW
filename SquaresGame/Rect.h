#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class SpriteRenderer;

class Rect {
    public:
        Rect(const GLuint width, const GLuint height);
        ~Rect();
        void update(const GLfloat dt);
        void draw(SpriteRenderer* renderer) const;
        bool isInside(double mouseX, double mouseY) const;

    private:
        GLfloat x, y, dx, dy;
        GLuint side;
        glm::vec3 color;
        GLuint width, height;
};
