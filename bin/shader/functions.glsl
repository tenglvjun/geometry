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

vec3 AmbientLight()
{
    return light.ambient * material.ambient * vec3(light.color.rgb);
}

vec3 DiffuseLight(vec3 norm, vec3 pos)
{
    vec3 lightDir = normalize(light.pos - pos);
    float diffuse = max(dot(normalize(norm), lightDir), 0.0);

    return light.diffuse * diffuse * material.diffuse * vec3(light.color.rgb);
}

vec3 SpecularLight(vec3 norm, vec3 pos)
{
    vec3 lightDir = normalize(light.pos - pos);
    vec3 viewDir = normalize(camera.pos - pos);
    vec3 reflectDir = reflect(lightDir, normalize(norm));  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    return light.specular * spec * material.specular * vec3(light.color.rgb);
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

vec4 ApplyLight(vec3 norm, vec3 pos)
{
    vec3 ambient = AmbientLight();
    vec3 diffuse = DiffuseLight(norm, pos);
    vec3 specular = SpecularLight(norm, pos);

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