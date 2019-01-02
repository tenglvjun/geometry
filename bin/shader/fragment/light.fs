struct Light
{
    uint source;
    vec3 pos;
    float ambientStrength;
    float specularStrength;
};

struct PointLightAttenuation
{
    float constant;
    float linear;
    float quadratic;
};

uniform Light light;
uniform PointLightAttenuation pointLightAttenuation;

vec3 ApplyPointLightAttenuation(vec3 color, vec3 pos)
{
    if (light.source != 1)
        return vec3(1.0, 1.0, 1.0);

    float distance = length(light.pos - pos);
    float constant = pointLightAttenuation.constant;
    float linear = pointLightAttenuation.linear;
    float quadratic = pointLightAttenuation.quadratic;

    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    color *= attenuation;  

    return color;
}