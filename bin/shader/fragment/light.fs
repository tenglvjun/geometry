struct Light
{
    uint source;

    vec3 pos;

    float ambientStrength;
    float specularStrength;

    // point light source attenuation parameters
    float constant;
    float linear;
    float quadratic;
};

uniform Light light;

vec3 AmbientLight(vec4 objColor)
{
    return light.ambientStrength * vec3(objColor.rgb);
}

vec3 DiffuseLight(vec3 norm, vec3 pos, vec4 objColor)
{
    vec3 lightDir = normalize(light.pos - pos);
    float diff = max(dot(normalize(norm), lightDir), 0.0);

    return diff * vec3(objColor.rgb);
}

vec3 SpecularLight(vec3 norm, vec3 eye, vec3 pos, vec4 objColor)
{
    vec3 lightDir = normalize(light.pos - pos);
    vec3 viewDir = normalize(eye - pos);
    vec3 reflectDir = reflect(-lightDir, normalize(norm));  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    return light.specularStrength * spec * vec3(objColor.rgb);
}

vec3 ApplyPointLightAttenuation(vec3 color, vec3 pos)
{
    if (light.source != 1)
        return vec3(1.0, 1.0, 1.0);

    float distance = length(light.pos - pos);
    float constant = light.constant;
    float linear = light.linear;
    float quadratic = light.quadratic;

    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    color *= attenuation;  

    return color;
}