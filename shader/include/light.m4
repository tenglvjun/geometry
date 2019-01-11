layout (std140) uniform LightBlock
{
    int source;

    vec3 pos;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec4 color;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
} light;