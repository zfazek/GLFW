#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

class SpriteRenderer;

class Rect {
    public:
        Rect(const GLuint width, const GLuint height);
        ~Rect();
        void update(const GLfloat deltaTime);
        void draw(SpriteRenderer* spriteRenderer) const;
        bool isInside(const double mouseX, const double mouseY) const;
        static void init(const GLuint width, const GLuint height);
        static std::string name;

    private:
        GLfloat x, y, dx, dy;
        GLuint side;
        glm::vec3 color;
        GLuint width, height;
};
