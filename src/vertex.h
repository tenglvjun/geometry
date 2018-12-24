#if !defined(__VERTEX_HEAD_FILE__)
#define __VERTEX_HEAD_FILE__

#include "vector.h"
#include "color.h"
#include "matrix.h"
#include <vector>

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

  void Flatten(std::vector<double> &buf);

  void Translate(const GeoVector3D &v);
  void Rotation(const GeoMatrix &m);

public:
  static unsigned int Size();
  static void Offset(std::vector<int> &offset);

protected:
  GeoVector3D m_pos;
  GeoVector3D m_normal;
  GeoColor m_color;
};

#endif // __VERTEX_HEAD_FILE__
