#include "quaternion.h"
#include <cmath>
#include "tools.h"

GeoQuaternion::GeoQuaternion()
    : m_s(0.0f)
{
}

GeoQuaternion::GeoQuaternion(const double s, const GeoVector3D &v)
    : m_s(s), m_v(v)
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

double GeoQuaternion::Angle() const
{
    return acos(m_s) * 2;
}

GeoVector3D GeoQuaternion::Axis() const
{
    GeoVector3D u = m_v;

    return u * (1 / sin(acos(m_s)));
}

GeoQuaternion GeoQuaternion::Rotation(const GeoVector3D &v, const GeoVector3D &axis, const double angle)
{
    GeoVector3D u = axis;
    u.Normalize();

    GeoQuaternion v1(0, v);

    double theta = Tools::GetInstance()->Radia2Degree(angle);
    theta *= 0.5;

    GeoQuaternion q(cos(theta), GeoVector3D(u * sin(theta)));

    return q * v1 * q.Inverse();
}

GeoMatrix GeoQuaternion::RotateMatrix(const GeoVector3D &axis, const double angle)
{
    GeoMatrix matrix(3, 3);

    GeoVector3D u = axis;
    u.Normalize();

    double theta = Tools::GetInstance()->Radia2Degree(angle);
    theta *= 0.5;

    double a = cos(theta);
    double b = sin(theta) * u[0];
    double c = sin(theta) * u[1];
    double d = sin(theta) * u[2];

    matrix[0][0] = 1 - 2 * c * c - 2 * d * d;
    matrix[0][1] = 2 * b * c - 2 * a * d;
    matrix[0][2] = 2 * a * c + 2 * b * d;

    matrix[1][0] = 2 * b * c + 2 * a * d;
    matrix[1][1] = 1 - 2 * b * b - 2 * d * d;
    matrix[1][2] = 2 * c * d - 2 * a * b;

    matrix[2][0] = 2 * b * d - 2 * a * c;
    matrix[2][1] = 2 * a * b + 2 * c * d;
    matrix[2][2] = 1 - 2 * b * b - 2 * c * c;

    return matrix;
}