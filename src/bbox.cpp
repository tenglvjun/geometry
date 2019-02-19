#include "bbox.h"
#include <iostream>

GeoBBox::GeoBBox()
{
}

GeoBBox::GeoBBox(const GeoVector3D &center, const GeoVector3D &min, const GeoVector3D &max)
    : m_center(center), m_min(min), m_max(max)
{
}

GeoBBox::GeoBBox(const GeoBBox &box)
{
    m_center = box.m_center;
    m_max = box.m_max;
    m_min = box.m_min;
}

GeoBBox::~GeoBBox()
{
}

GeoBBox &GeoBBox::operator=(const GeoBBox &box)
{
    if (this == &box)
    {
        return *this;
    }

    m_center = box.m_center;
    m_max = box.m_max;
    m_min = box.m_min;

    return *this;
}

void GeoBBox::CalBBox(std::vector<GeoVertex> &vertices)
{
    double min_x, min_y, min_z, max_x, max_y, max_z;

    min_x = min_y = min_z = 99999999999;
    max_x = max_y = max_z = -99999999999;

    for (std::vector<GeoVertex>::iterator iter = vertices.begin(); iter != vertices.end(); iter++)
    {
        GeoVector3D &pos = iter->GetPos();

        min_x = pos[0] < min_x ? pos[0] : min_x;
        min_y = pos[1] < min_y ? pos[1] : min_y;
        min_z = pos[2] < min_z ? pos[2] : min_z;

        max_x = pos[0] > max_x ? pos[0] : max_x;
        max_y = pos[1] > max_y ? pos[1] : max_y;
        max_z = pos[2] > max_z ? pos[2] : max_z;
    }

    m_min = GeoVector3D(min_x, min_y, min_z);
    m_max = GeoVector3D(max_x, max_y, max_z);

    m_center = (m_min + m_max) * 0.5;
}

const GeoVector3D &GeoBBox::GetMax() const
{
    return m_max;
}

const GeoVector3D &GeoBBox::GetMin() const
{
    return m_min;
}

const GeoVector3D &GeoBBox::GetCenter() const
{
    return m_center;
}

void GeoBBox::Dump() const
{
    std::cout << "Center: ";
    GetCenter().Dump();
    std::cout << "Max: ";
    GetMax().Dump();
    std::cout << "Min: ";
    GetMin().Dump();
}