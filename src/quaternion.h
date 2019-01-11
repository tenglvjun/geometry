#if !defined(__QUATERNION_HEAD_FILE__)
#define __QUATERNION_HEAD_FILE__

#include "vector.h"
#include "matrix.h"

class GeoQuaternion
{
  public:
    GeoQuaternion();
    GeoQuaternion(const double s, const GeoVector3D &v);
    GeoQuaternion(const GeoQuaternion &quat);
    virtual ~GeoQuaternion();

  public:
    GeoQuaternion &operator=(const GeoQuaternion &quat);
    GeoQuaternion operator+(const GeoQuaternion &quat);
    GeoQuaternion operator-(const GeoQuaternion &quat);
    GeoQuaternion operator*(const GeoQuaternion &quat);
    GeoQuaternion operator*(const double scale);
    void operator+=(const GeoQuaternion &quat);
    void operator-=(const GeoQuaternion &quat);
    void operator*=(const GeoQuaternion &quat);
    void operator*=(const double scale);

  public:
    void Normalize();
    double Magnitude() const;
    double Magnitude2() const;
    GeoQuaternion Pure();
    GeoQuaternion Conjugate();
    GeoQuaternion Inverse();
    double Angle() const;
    GeoVector3D Axis() const;

  public:
    static GeoQuaternion Rotation(const GeoVector3D &v, const GeoVector3D &axis, const double angle);
    static GeoMatrix RotateMatrix(const GeoVector3D &axis, const double angle);

  protected:
    double m_s;
    GeoVector3D m_v;
};

#endif // __QUATERNION_HEAD_FILE__
