#if !defined(__VERTEX_HEAD_FILE__)
#define __VERTEX_HEAD_FILE__

#include "vector.h"

class GeoVertex
{
public:
  GeoVertex();
  GeoVertex(const GeoVertex &v);
  virtual ~GeoVertex();

public:
  GeoVertex &operator=(const GeoVertex &v);

protected:
  GeoVector3D m_pos;
  GeoVector3D m_normal;
  GeoVector2D m_texCoords;
};

#endif // __VERTEX_HEAD_FILE__
