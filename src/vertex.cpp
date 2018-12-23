#include "vertex.h"
#include <assert.h>
#include <memory.h>

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

bool GeoVertex::Flatten(double *&buf, unsigned int length)
{
    unsigned int size = GeoVertex::Size();

    if (size > length)
    {
        assert(0);
        return false;
    }

    double b[size];
    memset(b, 0, sizeof(double) * size);

    b[0] = m_pos[0];
    b[1] = m_pos[1];
    b[2] = m_pos[2];

    b[3] = m_normal[0];
    b[4] = m_normal[1];
    b[5] = m_normal[2];

    b[6] = m_color[0];
    b[7] = m_color[1];
    b[8] = m_color[2];
    b[9] = m_color[3];

    memcpy(buf, b, sizeof(double) * size);

    return true;
}

unsigned int GeoVertex::Size()
{
    return (GeoVector3D::Size() + GeoVector3D::Size() + GeoColor::Size());
}
