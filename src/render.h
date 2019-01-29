#if !defined(__RENDER_HEAD_FILE__)
#define __RENDER_HEAD_FILE__

#include "global_def.h"
#include "camera.h"
#include "light.h"
#include "canvas.h"
#include "mesh.h"
#include "point.h"
#include <vector>

struct GeoViewport
{
  GeoViewport();
  GeoViewport(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height);

  unsigned int m_x;
  unsigned int m_y;
  unsigned int m_width;
  unsigned int m_height;
};

class GeoRender final
{
public:
  GeoRender();
  ~GeoRender();

public:
  SINGLETON_DECLARE(GeoRender);

public:
  void Render();
  void SetViewPort(const GeoViewport &viewport);

public:
  void SetCamera(const GeoVector3D &pos, const GeoVector3D &center, const GeoVector3D &up);
  GeoMatrix &ProjectMatrix();
  GeoMatrix &ViewMatrix();
  ProjType_e ProjectType();
  void Scale(bool enlarge);
  void SetFrustum(const GeoFrustum &frustum, const ProjType_e pt);

public:
  GeoMesh *GetMesh(const unsigned int idx);
  void DeleteMesh(const unsigned int idx);
  void AddMesh(GeoMesh *mesh);

public:
  GeoVector3D MapScreenToModel(const GeoVector3D &v, const unsigned int idx);
  GeoVector4D MapScreenToModel(const GeoVector4D &v, const unsigned int idx);
  GeoVector3D MapModelToScreen(const GeoVector3D &v, const unsigned int idx);
  GeoVector4D MapModelToScreen(const GeoVector4D &v, const unsigned int idx);

public:
  void BindCameraUniformBlock(const Shader &shader);
  void BindLightUniformBlock(const Shader &shader);

private:
  void Clear();

private:
  struct GeoViewport m_viewPort;
  GeoCamera m_camera;
  GeoLight m_light;
  GeoCanvas *m_canvas;
  std::vector<GeoMesh *> m_meshes;
};

#endif // __RENDER_HEAD_FILE__
