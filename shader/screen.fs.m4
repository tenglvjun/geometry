include(shader_version.m4)
out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D screenTexture;

void main()
{
    FragColor = texture(screenTexture, TexCoords);
} 