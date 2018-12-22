#include "vertex.h"

GeoVertex::GeoVertex()
{
}

GeoVertex::GeoVertex(const GeoVertex &v)
{
    m_pos = v.m_pos;
    m_normal = v.m_normal;
    m_color = v.m_color;
}

GeoVertex::~GeoVertex()
{
}

GeoVertex &GeoVertex::operator=(const GeoVertex &v)
{
    if (&v == this)
    {
        return *this;
    }
    m_pos = v.m_pos;
    m_normal = v.m_normal;
    m_color = v.m_color;

    return *this;
}

GeoVector3D &GeoVertex::GetPos()
{
    return m_pos;
}

GeoVector3D &GeoVertex::GetNormal()
{
    return m_normal;
}

GeoColor &GeoVertex::GetColor()
{
    return m_color;
}