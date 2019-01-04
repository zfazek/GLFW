#version 330 core
in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;
in vec3 spriteColor;
out vec4 fragColor;

uniform sampler2D image;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 color = (ambient + diffuse) * spriteColor;
    fragColor = vec4(color, 1.0f) * texture(image, texCoords);
}
