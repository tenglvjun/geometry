#include "mesh.h"
#include "global_def.h"
#include <iostream>
#include "camera.h"
#include "light.h"
#include "tools.h"
#include "shader_code_manage.h"

GeoMesh::GeoMesh(std::vector<GeoVertex> &vertices, std::vector<unsigned int> &indices, GeoVector3D &pos)
    : m_model(4, 4)
{
    m_vertices = vertices;
    m_indices = indices;
    m_pos = pos;
    m_model.SetIdentity();
    m_vao = m_vbo = m_ebo = 0;

    Setup();
}

GeoMesh::~GeoMesh()
{
    m_vertices.clear();
    m_indices.clear();

    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);

    m_vao = m_vbo = m_ebo = 0;
}

void GeoMesh::Draw()
{
    ApplyShader();

    // draw mesh
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GeoMesh::Setup()
{
    SetupVertices();
    SetupMaterial();
    SetupShaderCode();
    ApplyShader();
}

void GeoMesh::SetupVertices()
{
    unsigned int size = GeoVertex::Size();
    std::vector<double> buf;
    for (size_t i = 0; i < m_vertices.size(); i++)
    {
        m_vertices[i].Flatten(buf);
    }

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GeoVertex), &buf[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    std::vector<int> offset;
    GeoVertex::Offset(offset);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, size * sizeof(double), (void *)(offset[0] * sizeof(double)));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, size * sizeof(double), (void *)(offset[1] * sizeof(double)));

    glBindVertexArray(0);
}

void GeoMesh::SetupShaderCode()
{
    std::vector<std::string> vcVertex, vcFragment;

    const GeoShaderCode &meshCode = GeoShaderCodeMgr::GetInstance()->GetShaderCode(SCT_Mesh);
    const GeoShaderCode &functionsCode = GeoShaderCodeMgr::GetInstance()->GetShaderCode(SCT_Fuctions);
    const GeoShaderCode &uniformCode = GeoShaderCodeMgr::GetInstance()->GetShaderCode(SCT_Uniform);

    vcVertex.push_back(uniformCode.m_vertex);
    vcVertex.push_back(functionsCode.m_vertex);
    vcVertex.push_back(meshCode.m_vertex);
    vcFragment.push_back(uniformCode.m_vertex);
    vcFragment.push_back(functionsCode.m_vertex);
    vcFragment.push_back(meshCode.m_fragment);

    m_shader.SetShaderCodes(vcVertex, vcFragment);
    m_shader.Complie();

    GeoCamera::GetInstance()->BindUniformBlock(m_shader);
    GeoLight::GetInstance()->BindUniformBlock(m_shader);
}

void GeoMesh::SetupMaterial()
{
    m_material.Ambient(GeoVector3D(1.0f, 0.5f, 0.31f));
    m_material.Specular(GeoVector3D(0.5f, 0.5f, 0.5f));
    m_material.Diffuse(GeoVector3D(1.0f, 0.5f, 0.31f));
    m_material.Shininess(32.0f);
}

void GeoMesh::ApplyShader()
{
    if (m_shader.IsUsing())
        return;

    std::vector<float> value;
    m_model[0][3] = m_pos[0];
    m_model[1][3] = m_pos[1];
    m_model[2][3] = m_pos[2];
    m_model.Flatten(value);
    m_shader.SetMatrix("model", false, &value[0]);

    m_material.ApplyShader(m_shader);
}
