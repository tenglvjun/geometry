include(camera.m4)
include(uniform.m4)

vec4 ApplyModelMatrix(vec4 pos)
{
    return translate * model * pos;
}

vec4 ApplyCameraTransformation(vec4 pos)
{
    return camera.projection * camera.view * translate * model * pos;
}

vec3 TranslateNormal(vec3 normal)
{
    return mat3(transpose(inverse(translate * model))) * normal;
}