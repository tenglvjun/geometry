#if !defined(__POINT_HEAD_FILE__)
#define __POINT_HEAD_FILE__

#include "vector.h"

class GeoPoint2D
{
  public:
    GeoPoint2D();
    GeoPoint2D(const double x, const double y);
    GeoPoint2D(const GeoPoint2D &pt);
    virtual ~GeoPoint2D();

  public:
    GeoPoint2D &operator=(const GeoPoint2D &pt);
    double &operator[](const unsigned int idx);
    double operator[](const unsigned int idx) const;

  protected:
    double m_coord[2];
};

class GeoPoint3D
{
  public:
    GeoPoint3D();
    GeoPoint3D(const double x, const double y, const double z);
    GeoPoint3D(const GeoPoint3D &pt);
    virtual ~GeoPoint3D();

  public:
    GeoPoint3D &operator=(const GeoPoint3D &pt);
    double &operator[](const unsigned int idx);
    double operator[](const unsigned int idx) const;

  protected:
    double m_coord[3];
};

class GeoPoint4D
{
  public:
    GeoPoint4D();
    GeoPoint4D(const double x, const double y, const double z, const double w);
    GeoPoint4D(const GeoPoint4D &pt);
    virtual ~GeoPoint4D();

  public:
    GeoPoint4D &operator=(const GeoPoint4D &pt);
    double &operator[](const unsigned int idx);
    double operator[](const unsigned int idx) const;

  protected:
    double m_coord[4];
};

inline GeoVector2D operator-(const GeoPoint2D &e, const GeoPoint2D &s)
{
    GeoVector2D ret;

    ret[0] = e[0] - s[0];
    ret[1] = e[1] - s[1];

    return ret;
}

inline GeoVector3D operator-(const GeoPoint3D &e, const GeoPoint3D &s)
{
    GeoVector3D ret;

    ret[0] = e[0] - s[0];
    ret[1] = e[1] - s[1];
    ret[2] = e[2] - s[2];

    return ret;
}

inline GeoVector4D operator-(const GeoPoint4D &e, const GeoPoint4D &s)
{
    GeoVector4D ret;

    ret[0] = e[0] - s[0];
    ret[1] = e[1] - s[1];
    ret[2] = e[2] - s[2];
    ret[3] = e[3] - s[3];

    return ret;
}

#endif // __POINT_HEAD_FILE__
