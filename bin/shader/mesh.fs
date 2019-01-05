out vec4 FragColor;

in MESHVS_OUT {
    vec3 Normal;
    vec3 FragPos;
} MeshFrag_in;

void main()
{
    FragColor = ApplyLight(MeshFrag_in.Normal, MeshFrag_in.FragPos);
}