#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    texCoords = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
