#include "quaternion.h"
#include <cmath>

GeoQuaternion::GeoQuaternion()
    : m_s(0.0f)
{
}

GeoQuaternion::GeoQuaternion(const GeoQuaternion &quat)
{
    m_s = quat.m_s;
    m_v = quat.m_v;
}

GeoQuaternion::~GeoQuaternion()
{
}

GeoQuaternion &GeoQuaternion::operator=(const GeoQuaternion &quat)
{
    if (&quat == this)
    {
        return *this;
    }

    m_s = quat.m_s;
    m_v = quat.m_v;

    return *this;
}

GeoQuaternion GeoQuaternion::operator+(const GeoQuaternion &quat)
{
    GeoQuaternion ret;

    ret.m_s = m_s + quat.m_s;
    ret.m_v = m_v + quat.m_v;

    return ret;
}

GeoQuaternion GeoQuaternion::operator-(const GeoQuaternion &quat)
{
    GeoQuaternion ret;

    ret.m_s = m_s - quat.m_s;
    ret.m_v = m_v - quat.m_v;

    return ret;
}

GeoQuaternion GeoQuaternion::operator*(const GeoQuaternion &quat)
{
    GeoQuaternion ret;

    ret.m_s = (m_s * quat.m_s) - (m_v % quat.m_v);
    ret.m_v = quat.m_v * m_s + m_v * quat.m_s + m_v * quat.m_v;

    return ret;
}

GeoQuaternion GeoQuaternion::operator*(const double scale)
{
    GeoQuaternion ret;

    ret.m_s = m_s * scale;
    ret.m_v = m_v * scale;

    return ret;
}

void GeoQuaternion::operator+=(const GeoQuaternion &quat)
{
    m_s += quat.m_s;
    m_v += quat.m_v;
}

void GeoQuaternion::operator-=(const GeoQuaternion &quat)
{
    m_s -= quat.m_s;
    m_v -= quat.m_v;
}

void GeoQuaternion::operator*=(const GeoQuaternion &quat)
{
    double s = m_s;
    GeoVector3D v = m_v;

    m_s = (s * quat.m_s) - (v % quat.m_v);
    m_v = quat.m_v * s + v * quat.m_s + v * quat.m_v;
}

void GeoQuaternion::operator*=(const double scale)
{
    m_s *= scale;
    m_v *= scale;
}

void GeoQuaternion::Normalize()
{
    double magnitude = m_s * m_s + m_v.Magnitude2();

    magnitude = 1 / magnitude;

    m_s *= magnitude;
    m_v *= magnitude;
}

double GeoQuaternion::Magnitude() const
{
    return sqrt(m_s * m_s + m_v.Magnitude2());
}

double GeoQuaternion::Magnitude2() const
{
    return m_s * m_s + m_v.Magnitude2();
}

GeoQuaternion GeoQuaternion::Pure()
{
    GeoQuaternion ret;

    ret.m_v = m_v;

    return ret;
}

GeoQuaternion GeoQuaternion::Conjugate()
{
    GeoQuaternion ret;

    ret.m_s = m_s;
    ret.m_v = m_v * (-1);

    return ret;
}

GeoQuaternion GeoQuaternion::Inverse()
{
    GeoQuaternion ret;

    GeoQuaternion conjugate = Conjugate();
    double mag2 = Magnitude2();
    mag2 = 1 / mag2;

    ret.m_s = conjugate.m_s * mag2;
    ret.m_v = conjugate.m_v * mag2;

    return ret;
}