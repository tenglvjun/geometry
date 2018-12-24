#if !defined(__CAMERA_HEAD_FILE__)
#define __CAMERA_HEAD_FILE__

#include "vector.h"

class GeoCamera
{
  public:
    GeoCamera();
    GeoCamera(const GeoCamera &camera);
    virtual ~GeoCamera();

  public:
    GeoCamera &operator=(const GeoCamera &camera);

  public:
    void SetCamera(const GeoVector3D &pos, const GeoVector3D &up);

  protected:
    GeoVector3D m_pos;
    GeoVector3D m_dir;
    GeoVector3D m_up;
};

#endif // __CAMERA_HEAD_FILE__
