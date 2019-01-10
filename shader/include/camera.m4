layout (std140) uniform CameraBlock
{
    mat4 view;
    mat4 projection;
    vec3 pos;
} camera;

include(uniform.m4)

vec4 ApplyModelMatrix(vec4 pos)
{
    return model * pos;
}

vec4 ApplyCameraTransformation(vec4 pos)
{
    return camera.projection * camera.view * model * pos;
}

vec3 TranslateNormal(vec3 normal)
{
    return mat3(transpose(inverse(model))) * normal;
}