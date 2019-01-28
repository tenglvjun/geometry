#include "arcball.h"
#include <cmath>
#include "tools.h"
#include "quaternion.h"

GeoArcBall::GeoArcBall()
    : m_center(0.0f, 0.0f, 0.0f)
{
    m_radius = 1.0f;
}

GeoArcBall::GeoArcBall(const GeoArcBall &ball)
{
    m_center = ball.m_center;
    m_radius = ball.m_radius;
}

GeoArcBall::~GeoArcBall()
{
}

GeoArcBall &GeoArcBall::operator=(const GeoArcBall &ball)
{
    if (&ball == this)
    {
        return *this;
    }

    m_center = ball.m_center;
    m_radius = ball.m_radius;

    return *this;
}

GeoVector3D GeoArcBall::ProjectToSphere(const GeoVector3D &pt)
{
    GeoVector3D ret;

    ret[0] = pt[0];
    ret[1] = pt[1];

    double square = pt[0] * pt[0] + pt[1] * pt[1];

    if (square <= 1.0f)
    {
        ret[2] = sqrt(1.0 - square);
    }
    else
    {
        double length = sqrt(square);
        ret[0] /= length;
        ret[1] /= length;
        ret[2] = 0.0f;
    }

    return ret;
}

GeoMatrix GeoArcBall::GetRotateMatrix(const GeoVector3D &s, const GeoVector3D &e)
{
    GeoVector3D v1 = s;
    GeoVector3D v2 = e;

    v1.Normalize();
    v2.Normalize();

    GeoVector3D axis = v1 * v2;
    axis.Normalize();

    double angle = acos(v1 % v2);

    //    return GeoQuaternion::RotateMatrix(axis, angle);
    return GeoMatrix::RotateMatrix(angle, axis);
}