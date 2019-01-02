out vec4 FragColor;

in vec4 objectColor;
in vec3 Normal;
in vec3 FragPos;
in vec3 eyePos;

void main()
{
    vec3 ambient = AmbientLight(objectColor);
    vec3 diffuse = DiffuseLight(Normal, FragPos, objectColor);
    vec3 specular = SpecularLight(Normal, eyePos, FragPos, objectColor);

    ambient = ApplyPointLightAttenuation(ambient, FragPos);
    diffuse = ApplyPointLightAttenuation(diffuse, FragPos);
    specular = ApplyPointLightAttenuation(specular, FragPos);
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}