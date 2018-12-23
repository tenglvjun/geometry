#if !defined(__VECTOR_HEAD_FILE__)
#define __VECTOR_HEAD_FILE__

class GeoVector2D
{
public:
  GeoVector2D();
  GeoVector2D(const double x, const double y);
  GeoVector2D(const GeoVector2D &v);
  virtual ~GeoVector2D();

public:
  GeoVector2D &operator=(const GeoVector2D &v);
  double operator[](const unsigned int idx) const;
  double &operator[](const unsigned int idx);

public:
  static unsigned int Size();

protected:
  double m_coord[2];
};

class GeoVector3D
{
public:
  GeoVector3D();
  GeoVector3D(const double x, const double y, const double z);
  GeoVector3D(const GeoVector3D &v);
  virtual ~GeoVector3D();

public:
  GeoVector3D &operator=(const GeoVector3D &v);
  double operator[](const unsigned int idx) const;
  double &operator[](const unsigned int idx);

public:
  static unsigned int Size();

protected:
  double m_coord[3];
};

double operator%(const GeoVector3D &v1, const GeoVector3D &v2)
{
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[1] * v2[1];
}

#endif // __VECTOR_HEAD_FILE__
