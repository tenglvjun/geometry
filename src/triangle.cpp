#include "triangle.h"
#include <assert.h>
#include "matrix.h"

GeoTriangle::GeoTriangle(const GeoVector3D &a, const GeoVector3D &b, const GeoVector3D &c)
{
    m_vertices[0] = a;
    m_vertices[1] = b;
    m_vertices[2] = c;
}

GeoTriangle::GeoTriangle(const GeoTriangle &triangle)
{
    m_vertices[0] = triangle.m_vertices[0];
    m_vertices[1] = triangle.m_vertices[1];
    m_vertices[2] = triangle.m_vertices[2];
}

GeoTriangle::~GeoTriangle()
{
}

GeoTriangle &GeoTriangle::operator=(const GeoTriangle &triangle)
{
    if (&triangle == this)
    {
        return *this;
    }

    m_vertices[0] = triangle.m_vertices[0];
    m_vertices[1] = triangle.m_vertices[1];
    m_vertices[2] = triangle.m_vertices[2];

    return *this;
}

GeoVector3D &GeoTriangle::operator[](const unsigned int idx)
{
    assert(idx < 3);

    return m_vertices[idx];
}

bool GeoTriangle::PointInside(const GeoVector3D &point)
{
    GeoVector3D r = point - m_vertices[0];
    GeoVector3D q1 = m_vertices[1] - m_vertices[0];
    GeoVector3D q2 = m_vertices[2] - m_vertices[0];
    GeoVector2D rq(r % q1, r % q2);

    double dot11 = (q1 % q1);
    double dot22 = (q2 % q2);
    double dot12 = (q1 % q2);

    double factor = 1 / (dot11 * dot22 - dot12 * dot12);

    GeoMatrix m(2, 2);
    m[0][0] = dot22;
    m[0][1] = -dot12;
    m[1][0] = -dot12;
    m[1][1] = dot11;

    GeoVector2D w = m * rq * factor;

    return (w[0] + w[1] <= 1.0f);
}