#!/bin/bash

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

exit

#g++ youSource.cpp -I/usr/local/include -L/usr/local/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo
