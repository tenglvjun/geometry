layout (std140) uniform CameraBlock
{
    uniform mat4 view;
    uniform mat4 projection;
    uniform vec3 viewPos;
};

uniform mat4 model;

vec4 ApplyModelMatrix(vec4 pos)
{
    return model * pos;
}

vec4 ApplyCameraTransformation(vec4 pos)
{
    return projection * view * model * pos;
}

vec3 TranslateNormal(vec3 normal)
{
    return mat3(transpose(inverse(model))) * normal;
}

vec3 GetViewPos()
{
    return viewPos;
}