#include "render.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GeoViewport::GeoViewport()
{
    m_x = m_y = m_width = m_height = 0;
}

GeoViewport::GeoViewport(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}

SINGLETON_IMPLEMENT(GeoRender);

GeoRender::GeoRender()
{
}

GeoRender::~GeoRender()
{
}

void GeoRender::Render()
{
    glViewport(m_viewPort.m_x, m_viewPort.m_y, m_viewPort.m_width, m_viewPort.m_height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GeoRender::SetViewPort(const GeoViewport &viewport)
{
    m_viewPort = viewport;
}

void GeoRender::SetCamera(const GeoVector3D &pos, const GeoVector3D &center, const GeoVector3D &up)
{
    m_camera.ResetCamera(pos, center, up);
}

GeoMatrix &GeoRender::ProjectMatrix()
{
    return m_camera.GetProjectionMatrix();
}

GeoMatrix &GeoRender::ViewMatrix()
{
    return m_camera.GetViewMatrix();
}

ProjType_e GeoRender::ProjectType()
{
    return m_camera.GetProjectType();
}

void GeoRender::Scale(bool enlarge)
{
    m_camera.Scale(enlarge);
}

void GeoRender::SetFrustum(const GeoFrustum &frustum, const ProjType_e pt)
{
    m_camera.SetFrustum(frustum, pt);
}

void GeoRender::BindCameraUniformBlock(const Shader &shader)
{
    m_camera.BindUniformBlock(shader);
}