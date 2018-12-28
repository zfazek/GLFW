#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class LightRenderer;

class Light {
    public:
        Light(const GLuint x,
              const GLuint y,
              const GLuint z,
              glm::vec3 color);
        ~Light();
        void update(const GLfloat deltaTime);
        void draw(LightRenderer* lightRenderer, const glm::mat4 projection, const glm::mat4 view) const;
        glm::vec3 getColor() const;
        glm::vec3 getPosition() const;

    private:
        GLfloat side;
        GLfloat x, y, z;
        glm::vec3 color;
};
