#include "color.h"
#include <assert.h>
#include "tools.h"
#include <iostream>

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

GeoColor GeoColor::operator*(const GeoColor &color) const
{
    GeoColor ret;

    ret[0] = Tools::Minimum((m_rgba[0] * color[0]), 1.0f);
    ret[1] = Tools::Minimum((m_rgba[1] * color[1]), 1.0f);
    ret[2] = Tools::Minimum((m_rgba[2] * color[2]), 1.0f);
    ret[3] = Tools::Minimum((m_rgba[3] * color[3]), 1.0f);

    return ret;
}

GeoColor &GeoColor::operator*=(const GeoColor &color)
{
    m_rgba[0] = Tools::Minimum((m_rgba[0] * color[0]), 1.0f);
    m_rgba[1] = Tools::Minimum((m_rgba[1] * color[1]), 1.0f);
    m_rgba[2] = Tools::Minimum((m_rgba[2] * color[2]), 1.0f);
    m_rgba[3] = Tools::Minimum((m_rgba[3] * color[3]), 1.0f);

    return *this;
}

GeoColor GeoColor::operator+(const GeoColor &color) const
{
    GeoColor ret;

    ret[0] = Tools::Minimum((m_rgba[0] + color[0]), 1.0f);
    ret[1] = Tools::Minimum((m_rgba[1] + color[1]), 1.0f);
    ret[2] = Tools::Minimum((m_rgba[2] + color[2]), 1.0f);
    ret[3] = Tools::Minimum((m_rgba[3] + color[3]), 1.0f);

    return ret;
}

GeoColor &GeoColor::operator+=(const GeoColor &color)
{
    m_rgba[0] = Tools::Minimum((m_rgba[0] + color[0]), 1.0f);
    m_rgba[1] = Tools::Minimum((m_rgba[1] + color[1]), 1.0f);
    m_rgba[2] = Tools::Minimum((m_rgba[2] + color[2]), 1.0f);
    m_rgba[3] = Tools::Minimum((m_rgba[3] + color[3]), 1.0f);

    return *this;
}

void GeoColor::Scale(const double scale, bool applyAlpha)
{
    unsigned int count = GeoColor::Size();

    if (!applyAlpha)
    {
        count--;
    }

    for (size_t i = 0; i < count; i++)
    {
        m_rgba[i] = Tools::Minimum(m_rgba[i] * scale, 1.0f);
    }
}

void GeoColor::Flatten(std::vector<float> &data) const
{
    for (size_t i = 0; i < GeoColor::Size(); i++)
    {
        data.push_back((float)m_rgba[i]);
    }
}

double GeoColor::Red() const
{
    return m_rgba[0];
}

double GeoColor::Green() const
{
    return m_rgba[1];
}

double GeoColor::Blue() const
{
    return m_rgba[2];
}

double GeoColor::Alpha() const
{
    return m_rgba[3];
}

void GeoColor::Dump() const
{
    std::cout << "R: " << m_rgba[0] << " G: " << m_rgba[1] << " B: " << m_rgba[2] << " A: " << m_rgba[3] << std::endl;
}


unsigned int GeoColor::Size()
{
    return 4;
}
