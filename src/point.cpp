#include "point.h"
#include <assert.h>

GeoPoint2D::GeoPoint2D()
{
    m_coord[0] = m_coord[1] = 0.0f;
}

GeoPoint2D::GeoPoint2D(const double x, const double y)
{
    m_coord[0] = x;
    m_coord[1] = y;
}

GeoPoint2D::GeoPoint2D(const GeoPoint2D &pt)
{
    m_coord[0] = pt[0];
    m_coord[1] = pt[1];
}

GeoPoint2D::~GeoPoint2D()
{
}

GeoPoint2D &GeoPoint2D::operator=(const GeoPoint2D &pt)
{
    if (this == &pt)
    {
        return *this;
    }

    m_coord[0] = pt[0];
    m_coord[1] = pt[1];

    return *this;
}

double &GeoPoint2D::operator[](const unsigned int idx)
{
    assert(idx < 2);

    return m_coord[idx];
}

double GeoPoint2D::operator[](const unsigned int idx) const
{
    assert(idx == 2);

    return m_coord[idx];
}

GeoPoint3D::GeoPoint3D()
{
    m_coord[0] = m_coord[1] = m_coord[2] = 0.0f;
}

GeoPoint3D::GeoPoint3D(const double x, const double y, const double z)
{
    m_coord[0] = x;
    m_coord[1] = y;
    m_coord[2] = z;
}

GeoPoint3D::GeoPoint3D(const GeoPoint3D &pt)
{
    for (unsigned int i = 0; i < 3; i++)
    {
        m_coord[i] = pt[i];
    }
}

GeoPoint3D::~GeoPoint3D()
{
}

GeoPoint3D &GeoPoint3D::operator=(const GeoPoint3D &pt)
{
    if (this == &pt)
    {
        return *this;
    }

    for (unsigned int i = 0; i < 3; i++)
    {
        m_coord[i] = pt[i];
    }

    return *this;
}

double &GeoPoint3D::operator[](const unsigned int idx)
{
    assert(idx < 3);

    return m_coord[idx];
}

double GeoPoint3D::operator[](const unsigned int idx) const
{
    assert(idx < 3);

    return m_coord[idx];
}

GeoPoint4D::GeoPoint4D()
{
    for (unsigned int i = 0; i < 4; i++)
    {
        m_coord[i] = 0.0f;
    }
}

GeoPoint4D::GeoPoint4D(const double x, const double y, const double z, const double w)
{
    m_coord[0] = x;
    m_coord[1] = y;
    m_coord[2] = z;
    m_coord[3] = w;
}

GeoPoint4D::GeoPoint4D(const GeoPoint4D &pt)
{
    for (unsigned int i = 0; i < 4; i++)
    {
        m_coord[i] = pt[i];
    }
}

GeoPoint4D::~GeoPoint4D()
{
}

GeoPoint4D &GeoPoint4D::operator=(const GeoPoint4D &pt)
{
    if (this == &pt)
    {
        return *this;
    }

    for (unsigned int i = 0; i < 4; i++)
    {
        m_coord[i] = pt[i];
    }

    return *this;
}

double &GeoPoint4D::operator[](const unsigned int idx)
{
    assert(idx < 4);

    return m_coord[idx];
}

double GeoPoint4D::operator[](const unsigned int idx) const
{
    assert(idx < 4);

    return m_coord[idx];
}