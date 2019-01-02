out vec4 FragColor;

in vec4 objectColor;
in vec3 Normal;
in vec3 FragPos;
in vec3 eyePos;

void main()
{
    FragColor = ApplyLight(Normal, eyePos, FragPos, objectColor);
}