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
    void ResetCamera(const GeoVector3D &pos, const GeoVector3D &up);
    const GeoMatrix &GetMatrix() const;
    void Move(const GeoVector3D &v);
    void Rotate(const GeoMatrix &m);

  public:
    SINGLETON_DECLARE(GeoCamera);

  protected:
    GeoVector3D m_pos;
    GeoVector3D m_dir;
    GeoVector3D m_up;
    GeoVector3D m_left;
    GeoMatrix m_trans;
};

#endif // __CAMERA_HEAD_FILE__
