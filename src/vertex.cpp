#include "vertex.h"
#include <assert.h>
#include <memory.h>
#include "global_def.h"

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

void GeoVertex::Flatten(std::vector<double> &buf)
{
    buf.push_back(m_pos[0]);
    buf.push_back(m_pos[1]);
    buf.push_back(m_pos[2]);

    buf.push_back(m_normal[0]);
    buf.push_back(m_normal[1]);
    buf.push_back(m_normal[2]);

    buf.push_back(m_color[0]);
    buf.push_back(m_color[1]);
    buf.push_back(m_color[2]);
    buf.push_back(m_color[3]);
}

void GeoVertex::Translate(const GeoVector3D &v)
{
    m_pos += v;
}

void GeoVertex::Rotation(const GeoMatrix &m)
{
    m_pos = m * m_pos;
}

unsigned int GeoVertex::Size()
{
    return (GeoVector3D::Size() + GeoVector3D::Size() + GeoColor::Size());
}

void GeoVertex::Offset(std::vector<int> &offset)
{
    offset.push_back(0);
    offset.push_back(3);
    offset.push_back(6);
}
