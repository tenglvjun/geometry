#version 410 core
out vec4 FragColor;

in vec4 objectColor;
in vec3 Normal;
in vec3 FragPos;

struct Light
{
    uint type;

    vec3 pos;
    vec4 color;

    float ambientStrength;
    float specularStrength;

    //point light
    float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos; 
uniform Light light;

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
    if (type == 1)
    {
        float distance = length(light.pos - FragPos);
        attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    }
        
    vec3 result = (ambient + diffuse + specular) * vec3(objectColor.rgb);
    FragColor = vec4(result, 1.0);
}