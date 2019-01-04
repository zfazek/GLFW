#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aColor;
layout (location = 4) in mat4 mModel;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoords;
out vec3 spriteColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    spriteColor = aColor;
    fragPos = vec3(mModel * vec4(aPos, 1.0f));
    normal = aNormal;
    texCoords = vec2(aTexCoord.x, 1.0f - aTexCoord.y);
    gl_Position = projection * view * mModel * vec4(aPos, 1.0f);
}
