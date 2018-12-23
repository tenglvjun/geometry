#if !defined(__MESH_HEAD_FILE__)
#define __MESH_HEAD_FILE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "vertex.h"
#include "shader.h"

class GeoMesh
{
  public:
    GeoMesh(std::vector<GeoVertex>& vertices, std::vector<unsigned int>& indices);
    virtual ~GeoMesh();

  public:
    void Draw();

  private:
    GeoMesh();
    GeoMesh &operator=(const GeoMesh &mesh);

    void Setup();

  protected:
    std::vector<GeoVertex> m_vertices;
    std::vector<unsigned int> m_indices;
    unsigned int m_vao, m_vbo, m_ebo;
    Shader m_shader;
};

#endif // __MESH_HEAD_FILE__
