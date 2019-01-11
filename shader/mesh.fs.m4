include(shader_version.m4)
out vec4 FragColor;

include(light_func.m4)

in MESHVS_OUT {
    vec3 Normal;
    vec3 FragPos;
} MeshFrag_in;

void main()
{
    FragColor = ApplyLight(MeshFrag_in.Normal, MeshFrag_in.FragPos);
}