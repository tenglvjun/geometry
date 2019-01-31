#if !defined(__FRAME_HEAD_FILE__)
#define __FRAME_HEAD_FILE__

#include "vector.h"

class GeoFrame2D
{
  public:
    GeoFrame2D();
    GeoFrame2D(const GeoFrame2D &frame);
    virtual ~GeoFrame2D();

  public:
    GeoFrame2D &operator=(const GeoFrame2D &frame);

  public:
    void SetFrame(const GeoVector2D &x, const GeoVector2D &y);

  protected:
    GeoVector2D m_x;
    GeoVector2D m_y;
};

class GeoFrame3D
{
  public:
    GeoFrame3D();
    GeoFrame3D(const GeoFrame3D &frame);
    virtual ~GeoFrame3D();

  public:
    GeoFrame3D &operator=(const GeoFrame3D &frame);

  public:
    void SetFrame(const GeoVector3D &x, const GeoVector3D &y, const GeoVector3D &z);

  protected:
    GeoVector3D m_x;
    GeoVector3D m_y;
    GeoVector3D m_z;
};

#endif // __FRAME_HEAD_FILE__
