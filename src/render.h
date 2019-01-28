#if !defined(__RENDER_HEAD_FILE__)
#define __RENDER_HEAD_FILE__

#include "global_def.h"
#include "camera.h"

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
  void BindCameraUniformBlock(const Shader& shader);

private:
  struct GeoViewport m_viewPort;
  GeoCamera m_camera;
};

#endif // __RENDER_HEAD_FILE__
