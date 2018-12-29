#if !defined(__MESH_HEAD_FILE__)
#define __MESH_HEAD_FILE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "vertex.h"
#include "shader.h"
#include "matrix.h"

class GeoMesh
{
public:
  GeoMesh(std::vector<GeoVertex> &vertices, std::vector<unsigned int> &indices, GeoVector3D &pos);
  virtual ~GeoMesh();

public:
  void Draw();

private:
  GeoMesh();
  GeoMesh &operator=(const GeoMesh &mesh);

  void Setup();
  void UpdateMatrix();

protected:
  std::vector<GeoVertex> m_vertices;
  std::vector<unsigned int> m_indices;
  std::vector<GeoVector3D> m_normals;
  GeoVector3D m_pos;
  GeoMatrix m_model;
  unsigned int m_vao, m_vbo, m_ebo;
  Shader m_shader;
};

#endif // __MESH_HEAD_FILE__
