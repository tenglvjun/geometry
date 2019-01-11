include(shader_version.m4)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

include(camera_func.m4)

out MESHVS_OUT
{
    out vec3 Normal;
    out vec3 FragPos;
} MeshVS_out;

void main()
{
    MeshVS_out.FragPos = vec3(ApplyModelMatrix(vec4(aPos, 1.0)));
    MeshVS_out.Normal = TranslateNormal(aNormal);

    gl_Position = ApplyCameraTransformation(vec4(aPos, 1.0));
}
