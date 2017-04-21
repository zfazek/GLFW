#pragma once

#include <map>
#include <string>

#include <GL/glew.h>

class Shader;
class Texture2D;

class ResourceManager {
public:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2D> textures;

    ResourceManager();
    static Shader loadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, const std::string& name);
    static Shader getShader(const std::string& name);
    static Texture2D loadTexture(const GLchar *file, const GLboolean alpha, const std::string& name);
    static Texture2D getTexture(const std::string& name);
    static void clear();
private:
    static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
    static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};
