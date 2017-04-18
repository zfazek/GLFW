#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "SpriteRenderer.h"

class Rect {
    public:
        Rect(const GLuint width, const GLuint height);
        ~Rect();
        void update(const GLfloat dt);
        void draw() const;
        bool isInside(const double mouseX, const double mouseY) const;
        static void init(const GLuint width, const GLuint height);

    private:
        GLfloat x, y, dx, dy;
        GLuint side;
        glm::vec3 color;
        GLuint width, height;
        SpriteRenderer* renderer;
};
