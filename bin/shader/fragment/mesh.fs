#version 410 core
out vec4 FragColor;

in vec4 objectColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec4 lightColor;

uniform float ambientStrength;
uniform float specularStrength;

void main()
{
    // ambient
    vec3 ambient = ambientStrength * vec3(lightColor.xyz);
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(lightColor.xyz);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(lightColor.xyz);  
        
    vec3 result = (ambient + diffuse + specular) * vec3(objectColor.xyz);
    FragColor = vec4(result, 1.0);
}