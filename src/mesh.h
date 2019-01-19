#if !defined(__MESH_HEAD_FILE__)
#define __MESH_HEAD_FILE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "matrix.h"
#include "material.h"
#include "bbox.h"

class GeoMesh
{
public:
  GeoMesh(std::vector<GeoVertex> &vertices, std::vector<unsigned int> &indices);
  virtual ~GeoMesh();

public:
  void Draw();
  void Transform(const GeoMatrix &m);
  const GeoMatrix &GetModelMatrix();

private:
  GeoMesh();
  GeoMesh &operator=(const GeoMesh &mesh);

  void Setup();
  void SetupVertices();
  void SetupShaderCode();
  void SetupMaterial();
  void ApplyShader();

protected:
  std::vector<GeoVertex> m_vertices;
  std::vector<unsigned int> m_indices;
  std::vector<GeoVector3D> m_normals;
  GeoVector3D m_pos;
  GeoMatrix m_model;
  unsigned int m_vao, m_vbo, m_ebo;
  Shader m_shader;
  GeoMaterial m_material;
  GeoBBox m_bbox;
};

#endif // __MESH_HEAD_FILE__
