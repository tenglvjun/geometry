out vec4 FragColor;

in vec4 objectColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos; 

void main()
{
    // ambient
    vec3 ambient = light.ambientStrength * vec3(objectColor.rgb);
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.pos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(objectColor.rgb);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specularStrength * spec * vec3(objectColor.rgb);

    ambient = ApplyPointLightAttenuation(ambient, FragPos);
    diffuse = ApplyPointLightAttenuation(diffuse, FragPos);
    specular = ApplyPointLightAttenuation(specular, FragPos);
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}