#if !defined(__CAMERA_HEAD_FILE__)
#define __CAMERA_HEAD_FILE__

#include "vector.h"
#include "matrix.h"
#include "global_def.h"
#include "global_enum.h"
#include "shader.h"

struct GeoFrustum
{
  GeoFrustum();
  GeoFrustum(const double l, const double r, const double b, const double t, const double n, const double f);

  double m_left;
  double m_right;
  double m_top;
  double m_bottom;
  double m_near;
  double m_far;
};

class GeoCamera final
{
public:
  GeoCamera();
  virtual ~GeoCamera();

public:
  void ResetCamera(const GeoVector3D &pos, const GeoVector3D &center, const GeoVector3D &up);
  void SetFrustum(const GeoFrustum &frustum, ProjType_e pt);

  void Move(const GeoVector3D &v);
  void Rotate(const GeoMatrix &m);
  void Scale(bool enlarge);

  const GeoMatrix &GetViewMatrix() const;
  const GeoMatrix &GetProjectionMatrix() const;

  const GeoVector3D &Position() const;

  unsigned int GetUniformBlockIndex() const;
  unsigned int GetUniformBindingPoint() const;
  void BindUniformBlock(Shader &shader);

protected:
  void ClearUBO();
  void UpdateProjection();
  void InitShader();
  void InitUniformBuffer();
  void UpdateUniformBuffer();

public:
  SINGLETON_DECLARE(GeoCamera);

private:
  GeoCamera(const GeoCamera &camera);
  GeoCamera &operator=(const GeoCamera &camera);

protected:
  GeoVector3D m_pos;
  GeoVector3D m_center;
  GeoVector3D m_up;

  GeoVector3D m_front;
  GeoVector3D m_upOrtho;
  GeoVector3D m_side;

  GeoMatrix m_view;
  GeoMatrix m_projection;

  double m_sensitivity;
  GeoFrustum m_frustum;
  ProjType_e m_projType;

  Shader m_shader;
  unsigned int m_ubo;
  unsigned int m_bindingPoint;
};

#endif // __CAMERA_HEAD_FILE__
