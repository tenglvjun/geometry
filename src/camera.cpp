#include "camera.h"

SINGLETON_IMPLEMENT(GeoCamera);

GeoCamera::GeoCamera()
    : m_view(4, 4)
{
    m_view.SetIdentity();
}

GeoCamera::GeoCamera(const GeoCamera &camera)
    : m_view(4, 4)
{
    m_pos = camera.m_pos;
    m_font = camera.m_font;
    m_up = camera.m_up;
    m_side = camera.m_side;
    m_view = camera.m_view;
}

GeoCamera::~GeoCamera()
{
}

GeoCamera &GeoCamera::operator=(const GeoCamera &camera)
{
    if (&camera == this)
    {
        return *this;
    }

    m_pos = camera.m_pos;
    m_font = camera.m_font;
    m_up = camera.m_up;
    m_side = camera.m_side;
    m_view = camera.m_view;

    return *this;
}

void GeoCamera::ResetCamera(const GeoVector3D &pos, const GeoVector3D& center,  const GeoVector3D &up)
{
    m_pos = pos;
    
    m_font = center - m_pos;
    m_font.Normalize();

    m_side = m_font * up;
    m_side.Normalize();

    m_up = m_side * m_font;
    m_up.Normalize();

    m_view.SetIdentity();

    GeoMatrix m1(4, 4);
    m1.SetIdentity();
    m1[0][0] = m_side[0];
    m1[1][0] = m_side[1];
    m1[2][0] = m_side[2];
    m1[0][1] = m_up[0];
    m1[1][1] = m_up[1];
    m1[2][1] = m_up[2];
    m1[0][2] = -m_font[0];
    m1[1][2] = -m_font[1];
    m1[2][2] = -m_font[2];

    GeoMatrix m2(4, 4);
    m2.SetIdentity();
    m2[3][0] = -m_pos[0];
    m2[3][1] = -m_pos[1];
    m2[3][2] = -m_pos[2];

    m_view = m1 * m2;
}

const GeoMatrix &GeoCamera::GetViewMatrix() const
{
    return m_view;
}

void GeoCamera::Move(const GeoVector3D &v)
{
    m_view[0][3] += v[0];
    m_view[1][3] += v[1];
    m_view[2][3] += v[2];
}

void GeoCamera::Rotate(const GeoMatrix &m)
{
    GeoMatrix subMatrix = m_view.SubMatrix(0, 3, 0, 3);
    subMatrix = m * subMatrix;

    m_view.Replace(0, 0, subMatrix);
}