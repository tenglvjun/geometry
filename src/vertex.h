#if !defined(__VERTEX_HEAD_FILE__)
#define __VERTEX_HEAD_FILE__

#include "vector.h"
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

  void Flatten(std::vector<double> &buf);

  void Translate(const GeoVector3D &v);
  void Rotation(const GeoMatrix &m);

  GeoVector3D Position() const;
  void Position(const GeoVector3D &pos);

  GeoVector3D Normal() const;
  void Normal(const GeoVector3D &normal);

public:
  static unsigned int Size();
  static void Offset(std::vector<int> &offset);

protected:
  GeoVector3D m_pos;
  GeoVector3D m_normal;
};

#endif // __VERTEX_HEAD_FILE__
