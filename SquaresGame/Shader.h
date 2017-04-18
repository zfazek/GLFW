#pragma once

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    GLuint ID;
    Shader() { }
    Shader  &use();

    void compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr);
    void setFloat(const GLchar *name, const GLfloat value, const GLboolean useShader = false);
    void setInteger(const GLchar *name, const GLint value, const GLboolean useShader = false);
    void setVector2f(const GLchar *name, const GLfloat x, const GLfloat y, const GLboolean useShader = false);
    void setVector2f(const GLchar *name, const glm::vec2 &value, const GLboolean useShader = false);
    void setVector3f(const GLchar *name, const GLfloat x, GLfloat y, const GLfloat z, const GLboolean useShader = false);
    void setVector3f(const GLchar *name, const glm::vec3 &value, const GLboolean useShader = false);
    void setVector4f(const GLchar *name, const GLfloat x, GLfloat y, const GLfloat z, const GLfloat w, const GLboolean useShader = false);
    void setVector4f(const GLchar *name, const glm::vec4 &value, const GLboolean useShader = false);
    void setMatrix4fv(const GLchar *name, const glm::mat4 &matrix, const GLboolean useShader = false);
private:
    void checkCompileErrors(const GLuint object, const std::string& type);
};
