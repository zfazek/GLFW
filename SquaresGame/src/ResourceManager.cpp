#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL/SOIL.h>

#include "Texture.h"
#include "Shader.h"

std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;

ResourceManager::ResourceManager() {
}

Shader ResourceManager::loadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, const std::string& name) {
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return shaders[name];
}

Shader ResourceManager::getShader(const std::string& name) {
    return shaders.at(name);
}

Texture2D ResourceManager::loadTexture(const GLchar* file, const GLboolean alpha, const std::string& name) {
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
}

Texture2D ResourceManager::getTexture(const std::string& name) {
    return textures.at(name);
}

void ResourceManager::clear() {
    for (const auto& iter : shaders)
        glDeleteProgram(iter.second.ID);
    for (const auto& iter : textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile) {
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try {
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        if (gShaderFile != nullptr) {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception& e) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    Shader shader;
    shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, const GLboolean alpha) {
    Texture2D texture;
    if (alpha) {
        texture.internal_Format = GL_RGBA;
        texture.image_Format = GL_RGBA;
    }
    int width, height;
    unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    texture.generate(width, height, image);
    SOIL_free_image_data(image);
    return texture;
}
