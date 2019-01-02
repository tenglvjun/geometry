layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 color;

out vec4 objectColor;
out vec3 Normal;
out vec3 FragPos;
out vec3 eyePos;

void main()
{
    objectColor = color;

    FragPos = vec3(ApplyModelMatrix(vec4(aPos, 1.0)).xyz);
    Normal = vec3(TranslateNormal(vec4(aNormal, 1.0)).xyz);
    gl_Position = ApplyCameraTransformation(vec4(aPos, 1.0));
    eyePos = GetViewPos();
}