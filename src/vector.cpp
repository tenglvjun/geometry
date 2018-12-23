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
    assert(idx < GeoVector2D::Size());

    return m_coord[idx];
}

double &GeoVector2D::operator[](const unsigned int idx)
{
    assert(idx < GeoVector2D::Size());

    return m_coord[idx];
}

unsigned int GeoVector2D::Size()
{
    return 2;
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
    assert(idx < GeoVector3D::Size());

    return m_coord[idx];
}

unsigned int GeoVector3D::Size()
{
    return 3;
}

double &GeoVector3D::operator[](const unsigned int idx)
{
    assert(idx < GeoVector3D::Size());

    return m_coord[idx];
}

GeoVector4D::GeoVector4D()
{
    m_coord[0] = 0.0f;
    m_coord[1] = 0.0f;
    m_coord[2] = 0.0f;
    m_coord[3] = 0.0f;
}

GeoVector4D::GeoVector4D(const double x, const double y, const double z, const double w)
{
    m_coord[0] = x;
    m_coord[1] = y;
    m_coord[2] = z;
    m_coord[3] = w;
}

GeoVector4D::GeoVector4D(const GeoVector4D &v)
{
    m_coord[0] = v[0];
    m_coord[1] = v[1];
    m_coord[2] = v[2];
    m_coord[3] = v[3];
}

GeoVector4D::~GeoVector4D()
{
}

GeoVector4D &GeoVector4D::operator=(const GeoVector4D &v)
{
    if (&v == this)
    {
        return *this;
    }

    m_coord[0] = v[0];
    m_coord[1] = v[1];
    m_coord[2] = v[2];
    m_coord[3] = v[3];

    return *this;
}

double GeoVector4D::operator[](const unsigned int idx) const
{
    assert(idx < GeoVector4D::Size());

    return m_coord[idx];
}

double &GeoVector4D::operator[](const unsigned int idx)
{
    assert(idx < GeoVector4D::Size());

    return m_coord[idx];
}

unsigned int GeoVector4D::Size()
{
    return 4;
}