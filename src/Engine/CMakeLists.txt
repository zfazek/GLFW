include_directories("/usr/include/freetype2")

add_library(engine_lib
    Camera.cpp
    Cube.cpp
    CubeRenderer.cpp
    CubesRenderer.cpp
    GameBase.cpp
    Light.cpp
    LightRenderer.cpp
    ResourceManager.cpp
    Shader.cpp
    SpriteRenderer.cpp
    TextRenderer.cpp
    Texture.cpp
)

target_include_directories(engine_lib
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine_lib
    glfw
    GLEW
    GL
    freetype
)
