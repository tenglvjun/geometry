#include "color.h"
#include <assert.h>

GeoColor::GeoColor()
{
    m_rgba[0] = 0.0f;
    m_rgba[1] = 0.0f;
    m_rgba[2] = 0.0f;
    m_rgba[3] = 1.0f;
}

GeoColor::GeoColor(const double r, const double g, const double b, const double a)
{
    m_rgba[0] = r;
    m_rgba[1] = g;
    m_rgba[2] = b;
    m_rgba[3] = a;
}

GeoColor::GeoColor(const GeoColor &color)
{
    m_rgba[0] = color.m_rgba[0];
    m_rgba[1] = color.m_rgba[1];
    m_rgba[2] = color.m_rgba[2];
    m_rgba[3] = color.m_rgba[3];
}

GeoColor::~GeoColor()
{
}

GeoColor &GeoColor::operator=(const GeoColor &color)
{
    if (&color == this)
    {
        return *this;
    }

    m_rgba[0] = color.m_rgba[0];
    m_rgba[1] = color.m_rgba[1];
    m_rgba[2] = color.m_rgba[2];
    m_rgba[3] = color.m_rgba[3];

    return *this;
}

double GeoColor::operator[](const unsigned int idx) const
{
    assert(idx < 3);

    return m_rgba[idx];
}

double &GeoColor::operator[](const unsigned int idx)
{
    assert(idx < 4);

    return m_rgba[idx];
}

unsigned int GeoColor::Size()
{
    return 4;
}
