#include "mesh.h"

GeoMesh::GeoMesh(std::vector<GeoVertex>& vertices, std::vector<unsigned int>& indices)
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
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GeoMesh::Setup()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GeoVertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(GeoVertex), (void *)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, sizeof(GeoVertex), (void *)(3 * sizeof(double)));
    // vertex colors
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, sizeof(GeoVertex), (void *)(6 * sizeof(double)));

    glBindVertexArray(0);

    m_shader.Init("shader/vertex/mesh.vs", "shader/fragment/mesh.fs");
}
