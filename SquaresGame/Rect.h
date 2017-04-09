#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class SpriteRenderer;

class Rect {
    public:
        Rect(GLuint width, GLuint height);
        ~Rect();
        void update(GLfloat dt);
        void draw(SpriteRenderer* renderer);
        bool isInside(double mouseX, double mouseY);

    private:
        GLfloat x, y, dx, dy;
        GLuint side;
        glm::vec3 color;
        GLuint width, height;
};
