#pragma once

#include <GL/glew.h>

class Texture2D {
public:
    GLuint ID;
    GLuint width, height;
    GLuint internal_Format;
    GLuint image_Format;
    GLuint wrap_S;
    GLuint wrap_T;
    GLuint filter_Min;
    GLuint filter_Max;

    Texture2D();

    void generate(GLuint width, GLuint height, unsigned char* data);
    void bind() const;
};
