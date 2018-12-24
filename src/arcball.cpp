#include "arcball.h"
#include <math.h>

GeoArcBall::GeoArcBall()
    : m_center(0.0f, 0.0f, 0.0f)
{
    m_radius = 1.0f;
}

GeoArcBall::GeoArcBall(const GeoArcBall& ball)
{
    m_center = ball.m_center;
    m_radius = ball.m_radius;
}

GeoArcBall::~GeoArcBall()
{
    
}

GeoArcBall& GeoArcBall::operator=(const GeoArcBall& ball)
{
    if (&ball == this) 
    {
        return *this;
    }

    m_center = ball.m_center;
    m_radius = ball.m_radius;
    
    return *this;
}

GeoVector3D GeoArcBall::ProjectToBall(const GeoVector3D& pt)
{
    GeoVector3D ret;

    ret[0] = pt[0];
    ret[1] = pt[1];

    double powx = pow(pt[0], 2);
    double powy = pow(pt[1], 2);
    double powr = pow(m_radius, 2);
    double powr2 = powr/((double)2);

    
    if ((powx + powy) > powr2)
    {

        ret[2] = powr2 / sqrt(powx + powy);
    }
    
    else
    {
        ret[2] = sqrt(powr - powx - powy);
    }
    
    return ret;
}

GeoMatrix GeoArcBall::GetRotateMatrix(const GeoVector3D& p1, const GeoVector3D& p2)
{
    double c = (p1 % p2) / (p1.Magnitude() * p2.Magnitude());
    double angle = acos(c);
    
    GeoVector3D axis = p1 * p2;
    axis.Normalize();

    return GeoMatrix::RotateMatrix(angle, axis);
}