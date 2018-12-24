#include "mesh.h"
#include "global_def.h"
#include <iostream>

GeoMesh::GeoMesh(std::vector<GeoVertex> &vertices, std::vector<unsigned int> &indices)
    : m_trans(4, 4)
{
    m_vertices = vertices;
    m_indices = indices;
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
    m_shader.Use();

    // draw mesh
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GeoMesh::Translate(const GeoVector3D &v)
{
    m_trans[0][3] += v[0];
    m_trans[1][3] += v[1];
    m_trans[2][3] += v[2];

    std::vector<float> buf;
    m_trans.Flatten(buf);

    m_shader.SetMatrix("transform", false, &buf[0]);
}

void GeoMesh::Rotate(const GeoMatrix &m)
{
    GeoMatrix subMatrix = m_trans.SubMatrix(0, 3, 0, 3);
    subMatrix = m * subMatrix;

    m_trans.Replace(0, 0, subMatrix);

    std::vector<float> buf;
    m_trans.Flatten(buf);

    m_shader.SetMatrix("transform", false, &buf[0]);
}

void GeoMesh::Setup()
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
    // vertex colors
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_DOUBLE, GL_FALSE, size * sizeof(double), (void *)(offset[2] * sizeof(double)));

    glBindVertexArray(0);

    m_shader.Init("shader/vertex/mesh.vs", "shader/fragment/mesh.fs");

    m_trans.SetIdentity();

    std::vector<float> bufMatrix;
    m_trans.Flatten(bufMatrix);

    m_shader.SetMatrix("transform", false, &bufMatrix[0]);
}
