#include "frame.h"

GeoFrame2D::GeoFrame2D()
{
}

GeoFrame2D::GeoFrame2D(const GeoFrame2D &frame)
{
    m_x = frame.m_x;
    m_y = frame.m_y;
}

GeoFrame2D::~GeoFrame2D()
{
}

GeoFrame2D &GeoFrame2D::operator=(const GeoFrame2D &frame)
{
    if (this == &frame)
    {
        return *this;
    }

    m_x = frame.m_x;
    m_y = frame.m_y;

    return *this;
}

void GeoFrame2D::SetFrame(const GeoVector2D &x, const GeoVector2D &y)
{
    m_x = x;
    m_y = y;
}

GeoFrame3D::GeoFrame3D()
{
}

GeoFrame3D::GeoFrame3D(const GeoFrame3D &frame)
{
    m_x = frame.m_x;
    m_y = frame.m_y;
    m_z = frame.m_z;
}

GeoFrame3D::~GeoFrame3D()
{
}

GeoFrame3D &GeoFrame3D::operator=(const GeoFrame3D &frame)
{
    if (this == &frame)
    {
        return *this;
    }

    m_x = frame.m_x;
    m_y = frame.m_y;
    m_z = frame.m_z;

    return *this;
}

void GeoFrame3D::SetFrame(const GeoVector3D &x, const GeoVector3D &y, const GeoVector3D &z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}