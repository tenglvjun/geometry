#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 color;

out vec4 objectColor;
out vec3 Normal;
out vec3 FragPos;
out mat4 modelMatrix;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    objectColor = color;

    modelMatrix = model;

    vec4 pos = model * vec4(aPos, 1.0);
    FragPos = vec3(pos.xyz);

    pos = transpose(inverse(view * model)) * vec4(aNormal, 1.0);
    Normal = vec3(pos.xyz);

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}