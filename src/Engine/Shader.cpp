#include "Shader.h"

#include <iostream>

void Shader::use() {
    glUseProgram(ID);
}

void Shader::compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource) {
    GLuint sVertex, sFragment, gShader;
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX", vertexSource);
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT", fragmentSource);
    if (geometrySource != nullptr) {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY", geometrySource);
    }
    ID = glCreateProgram();
    glAttachShader(ID, sVertex);
    glAttachShader(ID, sFragment);
    if (geometrySource != nullptr) {
        glAttachShader(ID, gShader);
    }
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM", vertexSource);
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr) {
        glDeleteShader(gShader);
    }
}

void Shader::setFloat(const GLchar *name, const GLfloat value, const GLboolean useShader) {
    if (useShader) {
        use();
    }
    glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::setInteger(const GLchar *name, const GLint value, const GLboolean useShader) {
    if (useShader) {
        use();
    }
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setVector2f(const GLchar *name, const GLfloat x, const GLfloat y, const GLboolean useShader) {
    if (useShader) {
        use();
    }
    glUniform2f(glGetUniformLocation(ID, name), x, y);
}

void Shader::setVector2f(const GLchar *name, const glm::vec2 &value, const GLboolean useShader) {
    if (useShader) {
        use();
    }
    glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}

void Shader::setVector3f(const GLchar *name, const GLfloat x, const GLfloat y, const GLfloat z, const GLboolean useShader) {
    if (useShader) {
        use();
    }
    glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}

void Shader::setVector3f(const GLchar *name, const glm::vec3 &value, const GLboolean useShader) {
    if (useShader) {
        use();
    }
    glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const GLchar *name, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w, const GLboolean useShader) {
    if (useShader) {
        use();
    }
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}

void Shader::setVector4f(const GLchar *name, const glm::vec4 &value, const GLboolean useShader) {
    if (useShader) {
        use();
    }
    glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4fv(const GLchar *name, const glm::mat4 &matrix, const GLboolean useShader) {
    if (useShader) {
        use();
    }
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(const GLuint object, const std::string& type, const std::string& name) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << " Name: " << name << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << " Name: " << name << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}
