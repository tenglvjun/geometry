#if !defined(__TRIANGLE_HEAD_FILE__)
#define __TRIANGLE_HEAD_FILE__

#include "vector.h"

class GeoTriangle
{
  public:
    GeoTriangle(const GeoVector3D &a, const GeoVector3D &b, const GeoVector3D &c);
    GeoTriangle(const GeoTriangle &triangle);
    virtual ~GeoTriangle();

  public:
    GeoTriangle &operator=(const GeoTriangle &triangle);
    GeoVector3D &operator[](const unsigned int idx);

  public:
    bool PointInside(const GeoVector3D &point);

  private:
    GeoTriangle();

  protected:
    GeoVector3D m_vertices[3];
};

#endif // __TRIANGLE_HEAD_FILE__
