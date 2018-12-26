#if !defined(__CAMERA_HEAD_FILE__)
#define __CAMERA_HEAD_FILE__

#include "vector.h"
#include "matrix.h"
#include "global_def.h"

class GeoCamera
{
  public:
    GeoCamera();
    GeoCamera(const GeoCamera &camera);
    virtual ~GeoCamera();

  public:
    GeoCamera &operator=(const GeoCamera &camera);

  public:
    void ResetCamera(const GeoVector3D &pos, const GeoVector3D& center,  const GeoVector3D &up);
    void SetFrustum(const double left, const double right, const double top, const double bottom, const double near, const double far);
    void Move(const GeoVector3D &v);
    void Rotate(const GeoMatrix &m);
    const GeoMatrix &GetViewMatrix() const;
    const GeoMatrix &GetProjectionMatrix() const;

  public:
    SINGLETON_DECLARE(GeoCamera);

  protected:
    GeoVector3D m_pos;
    GeoVector3D m_font;
    GeoVector3D m_up;
    GeoVector3D m_side;
    GeoMatrix m_view;
    GeoMatrix m_projection;
};

#endif // __CAMERA_HEAD_FILE__
