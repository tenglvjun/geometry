#version 410 core
out vec4 FragColor;

in vec4 objectColor;
in vec3 Normal;
in vec3 FragPos;

struct Light
{
    uint source;

    vec3 pos;
    vec4 color;

    float ambientStrength;
    float specularStrength;
};

struct PointLightAttenuation
{
    uint range;
    float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos; 
uniform Light light;
uniform PointLightAttenuation pointLightAttenuation[12];

void main()
{
    // ambient
    vec3 ambient = light.ambientStrength * vec3(light.color.rgb);
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.pos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(light.color.rgb);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specularStrength * spec * vec3(light.color.rgb);

    float attenuation = 1.0;
    if (light.source == 1)
    {
        float distance = length(light.pos - FragPos);
        
        float constant, linear, quadratic;
        
        for(int i = 0; i < 12; i++)
        {
            if (length(FragPos) < pointLightAttenuation[i].range)
            {
                constant = pointLightAttenuation[i].constant;
                linear = pointLightAttenuation[i].linear;
                quadratic = pointLightAttenuation[i].quadratic;
                break;
            }
        }

        attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
    }
        
    vec3 result = (ambient + diffuse + specular) * attenuation * vec3(objectColor.rgb);
    FragColor = vec4(result, 1.0);
}