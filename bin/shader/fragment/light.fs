struct Light
{
    uint source;

    vec3 pos;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // point light source parameters
    float constant;
    float linear;
    float quadratic;

    // spot light source parameters
    float cutOff;
    float outerCutOff;
};

uniform Light light;

vec3 AmbientLight(vec4 objColor)
{
    return light.ambient * vec3(objColor.rgb);
}

vec3 DiffuseLight(vec3 norm, vec3 pos, vec4 objColor)
{
    vec3 lightDir = normalize(light.pos - pos);
    float diffuse = max(dot(normalize(norm), lightDir), 0.0);

    return light.diffuse * diffuse * vec3(objColor.rgb);
}

vec3 SpecularLight(vec3 norm, vec3 eye, vec3 pos, vec4 objColor)
{
    vec3 lightDir = normalize(light.pos - pos);
    vec3 viewDir = normalize(eye - pos);
    vec3 reflectDir = reflect(lightDir, normalize(norm));  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    return light.specular * spec * vec3(objColor.rgb);
}

vec3 ApplyPointLightAttenuation(vec3 color, vec3 pos)
{
    float distance = length(light.pos - pos);
    float constant = light.constant;
    float linear = light.linear;
    float quadratic = light.quadratic;

    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    color *= attenuation;  

    return color;
}

vec4 ApplyLight(vec3 norm, vec3 eye, vec3 pos, vec4 objColor)
{
    vec3 ambient = AmbientLight(objColor);
    vec3 diffuse = DiffuseLight(norm, pos, objColor);
    vec3 specular = SpecularLight(norm, eye, pos, objColor);

    if (light.source == 0) 
        return vec4(ambient + diffuse + specular, 1.0);

    if (light.source == 2)
    {
        float theta = dot(normalize(pos - light.pos), normalize(-light.pos)); 
        float epsilon = (light.cutOff - light.outerCutOff);
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

        diffuse *= intensity;
        specular *= intensity;
    }

    ambient = ApplyPointLightAttenuation(ambient, pos);
    diffuse = ApplyPointLightAttenuation(diffuse, pos);
    specular = ApplyPointLightAttenuation(specular, pos);

    return vec4(ambient + diffuse + specular, 1.0);
}