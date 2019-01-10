#version 410 core
out vec4 FragColor;

include(light.m4)

in MESHVS_OUT {
    vec3 Normal;
    vec3 FragPos;
} MeshFrag_in;

void main()
{
    FragColor = ApplyLight(MeshFrag_in.Normal, MeshFrag_in.FragPos);
}