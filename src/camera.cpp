#include "camera.h"

SINGLETON_IMPLEMENT(GeoCamera);

GeoCamera::GeoCamera()
    : m_trans(4, 4)
{
    m_trans.SetIdentity();
}

GeoCamera::GeoCamera(const GeoCamera &camera)
    : m_trans(4, 4)
{
    m_pos = camera.m_pos;
    m_dir = camera.m_dir;
    m_up = camera.m_up;
    m_left = camera.m_left;
    m_trans = camera.m_trans;
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
    m_dir = camera.m_dir;
    m_up = camera.m_up;
    m_left = camera.m_left;
    m_trans = camera.m_trans;

    return *this;
}

void GeoCamera::ResetCamera(const GeoVector3D &pos, const GeoVector3D &up)
{
    m_pos = pos;
    
    m_dir = m_pos - GeoVector3D(0.0f, 0.0f, 0.0f);
    m_dir.Normalize();

    m_up = up;
    m_up.Normalize();

    m_left = m_dir * m_up;
    m_left.Normalize();

    m_trans.SetIdentity();
}

const GeoMatrix &GeoCamera::GetMatrix() const
{
    return m_trans;
}

void GeoCamera::Move(const GeoVector3D &v)
{
    m_trans[0][3] += v[0];
    m_trans[1][3] += v[1];
    m_trans[2][3] += v[2];
}

void GeoCamera::Rotate(const GeoMatrix &m)
{
    GeoMatrix subMatrix = m_trans.SubMatrix(0, 3, 0, 3);
    subMatrix = m * subMatrix;

    m_trans.Replace(0, 0, subMatrix);
}