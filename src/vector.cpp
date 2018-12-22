#include "vector.h"
#include <assert.h>

GeoVector2D::GeoVector2D()
{
    m_coord[0] = 0.0f;
    m_coord[1] = 0.0f;
}

GeoVector2D::GeoVector2D(const double x, const double y)
{
    m_coord[0] = x;
    m_coord[1] = y;
}

GeoVector2D::GeoVector2D(const GeoVector2D &v)
{
    m_coord[0] = v[0];
    m_coord[1] = v[1];
}

GeoVector2D::~GeoVector2D()
{
}

GeoVector2D &GeoVector2D::operator=(const GeoVector2D &v)
{
    if (&v == this)
    {
        return *this;
    }

    m_coord[0] = v[0];
    m_coord[1] = v[1];

    return *this;
}

double GeoVector2D::operator[](const unsigned int idx) const
{
    assert(idx < 2);

    return m_coord[idx];
}

double &GeoVector2D::operator[](const unsigned int idx)
{
    assert(idx < 2);

    return m_coord[idx];
}

GeoVector3D::GeoVector3D()
{
    m_coord[0] = 0.0f;
    m_coord[1] = 0.0f;
    m_coord[2] = 0.0f;
}

GeoVector3D::GeoVector3D(const double x, const double y, const double z)
{
    m_coord[0] = x;
    m_coord[1] = y;
    m_coord[2] = z;
}

GeoVector3D::GeoVector3D(const GeoVector3D &v)
{
    m_coord[0] = v[0];
    m_coord[1] = v[1];
    m_coord[2] = v[2];
}

GeoVector3D::~GeoVector3D()
{
}

GeoVector3D &GeoVector3D::operator=(const GeoVector3D &v)
{
    if (&v == this)
    {
        return *this;
    }

    m_coord[0] = v[0];
    m_coord[1] = v[1];
    m_coord[2] = v[2];

    return *this;
}

double GeoVector3D::operator[](const unsigned int idx) const
{
    assert(idx < 3);

    return m_coord[idx];
}

double &GeoVector3D::operator[](const unsigned int idx)
{
    assert(idx < 3);

    return m_coord[idx];
}