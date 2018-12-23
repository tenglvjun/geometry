#if !defined(__VERTEX_HEAD_FILE__)
#define __VERTEX_HEAD_FILE__

#include "vector.h"
#include "color.h"

class GeoVertex
{
public:
  GeoVertex();
  GeoVertex(const GeoVertex &v);
  virtual ~GeoVertex();

public:
  GeoVertex &operator=(const GeoVertex &v);

public:
  GeoVector3D &GetPos();
  GeoVector3D &GetNormal();
  GeoColor &GetColor();

  bool Flatten(double *&buf, unsigned int length);

public:
  static unsigned int Size();

protected:
  GeoVector3D m_pos;
  GeoVector3D m_normal;
  GeoColor m_color;
};

#endif // __VERTEX_HEAD_FILE__
