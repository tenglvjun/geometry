#if !defined(__MESH_HEAD_FILE__)
#define __MESH_HEAD_FILE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "matrix.h"
#include "material.h"
#include "bbox.h"
#include "global_enum.h"
#include "arcball.h"

class GeoMesh
{
public:
  GeoMesh(std::vector<GeoVertex> &vertices, std::vector<unsigned int> &indices);
  virtual ~GeoMesh();

public:
  void Draw();
  void Transform(const GeoMatrix &m);
  GeoMatrix &GetModelMatrix();
  GeoBBox &GetBBox();

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
  unsigned int m_vao, m_vbo, m_ebo;
  Shader m_shader;
  GeoMaterial m_material;
  GeoBBox m_bbox;
  GeoMatrix m_model;
};

#endif // __MESH_HEAD_FILE__
