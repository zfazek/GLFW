#!/bin/bash

g++ \
    -std=c++11 \
    SquaresGame.cpp \
    Game.cpp \
    ResourceManager.cpp \
    Shader.cpp \
    SpriteRenderer.cpp \
    Texture.cpp \
    -lglfw \
    -lGLEW \
    -lGL \
    -lSOIL \
    -lX11 \
    -lpthread \
    -lXrandr \
    -lXi \
    -o SquaresGame

exit

g++ \
    -std=c++11 \
    SquaresGame.cpp \
    Game.cpp \
    ResourceManager.cpp \
    Shader.cpp \
    SpriteRenderer.cpp \
    Texture.cpp \
    -I/usr/local/include \
    -L/usr/local/lib \
    -lglfw.3 \
    -lGLEW \
    -lSOIL \
    -framework OpenGL \
    -o SquaresGame
