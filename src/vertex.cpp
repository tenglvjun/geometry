#include "vertex.h"

GeoVertex::GeoVertex()
{
}

GeoVertex::GeoVertex(const GeoVertex &v)
{
    m_pos = v.m_pos;
    m_normal = v.m_normal;
    m_texCoords = v.m_texCoords;
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
    m_texCoords = v.m_texCoords;

    return *this;
}