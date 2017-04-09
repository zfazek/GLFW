#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"

class SpriteRenderer {
public:
    SpriteRenderer(const Shader& shader);
    ~SpriteRenderer();

    void drawSprite(const Texture2D& texture, const glm::vec2 position, const glm::vec2 size = glm::vec2(100, 100), const GLfloat rotate = 0.0f, const glm::vec3 color = glm::vec3(1.0f));
private:
    Shader shader; 
    GLuint quadVAO;
    void initRenderData();
};

#endif
