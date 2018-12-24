#include "camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GeoCamera::GeoCamera()
{
}

GeoCamera::GeoCamera(const GeoCamera &camera)
{
    m_pos = camera.m_pos;
    m_dir = camera.m_dir;
    m_up = camera.m_up;
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

    return *this;
}

void GeoCamera::SetCamera(const GeoVector3D &pos, const GeoVector3D &up)
{
    m_pos = pos;
    m_dir = m_pos - GeoVector3D(0.0f, 0.0f, 0.0f);
    m_dir.Normalize();
    m_up = up;
}