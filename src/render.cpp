#include "render.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include "matrix.h"

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
    : m_canvas(nullptr)
{
}

GeoRender::~GeoRender()
{
    Clear();
}

void GeoRender::Render()
{
    glViewport(m_viewPort.m_x, m_viewPort.m_y, m_viewPort.m_width, m_viewPort.m_height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_canvas->Active();

    for (std::vector<GeoMesh *>::iterator iter = m_meshes.begin(); iter != m_meshes.end(); iter++)
    {
        assert(*iter);

        (*iter)->Draw();
    }

    m_canvas->Deactive();
}

void GeoRender::SetViewPort(const GeoViewport &viewport)
{
    m_viewPort = viewport;

    SAFE_DELETE(m_canvas);
    m_canvas = new GeoCanvas(viewport.m_width, viewport.m_height);
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

GeoMesh *GeoRender::GetMesh(const unsigned int idx)
{
    assert(idx < m_meshes.size());

    return m_meshes[idx];
}

void GeoRender::DeleteMesh(const unsigned int idx)
{
    assert(idx < m_meshes.size());

    std::vector<GeoMesh *>::iterator iter = m_meshes.begin() + idx;

    SAFE_DELETE(*iter);

    m_meshes.erase(iter);
}

void GeoRender::AddMesh(GeoMesh *mesh)
{
    for (std::vector<GeoMesh *>::iterator iter = m_meshes.begin(); iter != m_meshes.end(); iter++)
    {
        if ((*iter) == mesh)
        {
            return;
        }
    }

    m_meshes.push_back(mesh);
}

GeoVector3D GeoRender::MapScreenToModel(const GeoVector3D &v, const unsigned int idx)
{
    assert(idx < m_meshes.size());

    GeoVector4D v1(v, 1.0f);

    v1 = MapScreenToModel(v1, idx);

    return GeoVector3D(v1[0], v1[1], v1[2]);
}

GeoVector4D GeoRender::MapScreenToModel(const GeoVector4D &v, const unsigned int idx)
{
    assert(idx < m_meshes.size());

    GeoMatrix &project = GeoRender::GetInstance()->ProjectMatrix();
    GeoMatrix &view = GeoRender::GetInstance()->ViewMatrix();
    GeoMatrix &model = m_meshes[idx]->GetModelMatrix();

    GeoMatrix pv = project * view;
    GeoMatrix pv_inverse(4, 4);
    pv.Inverse(pv_inverse);

    return (pv_inverse * v);
}

GeoVector3D GeoRender::MapModelToScreen(const GeoVector3D &v, const unsigned int idx)
{
    assert(idx < m_meshes.size());

    GeoVector4D v1(v, 1.0f);

    v1 = MapModelToScreen(v1, idx);

    return GeoVector3D(v1[0], v1[1], v1[2]);
}

GeoVector4D GeoRender::MapModelToScreen(const GeoVector4D &v, const unsigned int idx)
{
    assert(idx < m_meshes.size());

    GeoMatrix &project = GeoRender::GetInstance()->ProjectMatrix();
    GeoMatrix &view = GeoRender::GetInstance()->ViewMatrix();
    GeoMatrix &model = m_meshes[idx]->GetModelMatrix();

    return project * view * model * v;
}

void GeoRender::BindCameraUniformBlock(const Shader &shader)
{
    m_camera.BindUniformBlock(shader);
}

void GeoRender::BindLightUniformBlock(const Shader &shader)
{
    m_light.BindUniformBlock(shader);
}

void GeoRender::Clear()
{
    for (std::vector<GeoMesh *>::iterator iter = m_meshes.begin(); iter != m_meshes.end(); iter++)
    {
        SAFE_DELETE(*iter);
    }

    m_meshes.clear();

    SAFE_DELETE(m_canvas);
}