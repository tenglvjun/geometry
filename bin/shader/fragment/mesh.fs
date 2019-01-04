out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 eyePos;

void main()
{
    FragColor = ApplyLight(Normal, eyePos, FragPos);
}