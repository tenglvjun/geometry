uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;

vec4 ApplyModelMatrix(vec4 pos)
{
    return model * pos;
}

vec4 ApplyCameraTransformation(vec4 pos)
{
    return projection * view * model * pos;
}

vec4 TranslateNormal(vec4 normal)
{
    return transpose(inverse(view * model)) * normal;
}

vec3 GetViewPos()
{
    return viewPos;
}