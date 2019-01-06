layout (std140) uniform LightBlock
{
    int source;

    vec3 pos;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec4 color;

    // point light source parameters
    float constant;
    float linear;
    float quadratic;

    // spot light source parameters
    float cutOff;
    float outerCutOff;
} light;

void main()
{
    
}