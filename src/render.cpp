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
    : m_canvas(nullptr), m_mesh(nullptr)
{

    std::vector<GeoVertex> vertices;
    std::vector<unsigned int> indices;

    float data[] = {
        // positions          // normals
        -0.3f, -0.3f, -0.3f,  0.0f,  0.0f, -1.0f,
         0.3f, -0.3f, -0.3f,  0.0f,  0.0f, -1.0f,
         0.3f,  0.3f, -0.3f,  0.0f,  0.0f, -1.0f,
         0.3f,  0.3f, -0.3f,  0.0f,  0.0f, -1.0f,
        -0.3f,  0.3f, -0.3f,  0.0f,  0.0f, -1.0f,
        -0.3f, -0.3f, -0.3f,  0.0f,  0.0f, -1.0f,

        -0.3f, -0.3f,  0.3f,  0.0f,  0.0f,  1.0f,
         0.3f, -0.3f,  0.3f,  0.0f,  0.0f,  1.0f,
         0.3f,  0.3f,  0.3f,  0.0f,  0.0f,  1.0f,
         0.3f,  0.3f,  0.3f,  0.0f,  0.0f,  1.0f,
        -0.3f,  0.3f,  0.3f,  0.0f,  0.0f,  1.0f,
        -0.3f, -0.3f,  0.3f,  0.0f,  0.0f,  1.0f,

        -0.3f,  0.3f,  0.3f, -1.0f,  0.0f,  0.0f,
        -0.3f,  0.3f, -0.3f, -1.0f,  0.0f,  0.0f,
        -0.3f, -0.3f, -0.3f, -1.0f,  0.0f,  0.0f,
        -0.3f, -0.3f, -0.3f, -1.0f,  0.0f,  0.0f,
        -0.3f, -0.3f,  0.3f, -1.0f,  0.0f,  0.0f,
        -0.3f,  0.3f,  0.3f, -1.0f,  0.0f,  0.0f,

         0.3f,  0.3f,  0.3f,  1.0f,  0.0f,  0.0f,
         0.3f,  0.3f, -0.3f,  1.0f,  0.0f,  0.0f,
         0.3f, -0.3f, -0.3f,  1.0f,  0.0f,  0.0f,
         0.3f, -0.3f, -0.3f,  1.0f,  0.0f,  0.0f,
         0.3f, -0.3f,  0.3f,  1.0f,  0.0f,  0.0f,
         0.3f,  0.3f,  0.3f,  1.0f,  0.0f,  0.0f,

        -0.3f, -0.3f, -0.3f,  0.0f, -1.0f,  0.0f,
         0.3f, -0.3f, -0.3f,  0.0f, -1.0f,  0.0f,
         0.3f, -0.3f,  0.3f,  0.0f, -1.0f,  0.0f,
         0.3f, -0.3f,  0.3f,  0.0f, -1.0f,  0.0f,
        -0.3f, -0.3f,  0.3f,  0.0f, -1.0f,  0.0f,
        -0.3f, -0.3f, -0.3f,  0.0f, -1.0f,  0.0f,

        -0.3f,  0.3f, -0.3f,  0.0f,  1.0f,  0.0f,
         0.3f,  0.3f, -0.3f,  0.0f,  1.0f,  0.0f,
         0.3f,  0.3f,  0.3f,  0.0f,  1.0f,  0.0f,
         0.3f,  0.3f,  0.3f,  0.0f,  1.0f,  0.0f,
        -0.3f,  0.3f,  0.3f,  0.0f,  1.0f,  0.0f,
        -0.3f,  0.3f, -0.3f,  0.0f,  1.0f,  0.0f,
    };

    for (unsigned int i = 0; i < 36; i++)
    {
        GeoVertex vertex;

        GeoVector3D pos, normal;

        pos[0] = data[i * 6];
        pos[1] = data[i * 6 + 1];
        pos[2] = data[i * 6 + 2];

        normal[0] = data[i * 6 + 3];
        normal[1] = data[i * 6 + 4];
        normal[2] = data[i * 6 + 5];

        vertex.Position(pos);
        vertex.Normal(normal);

        vertices.push_back(vertex);
        indices.push_back(i);
    }

    m_mesh = new GeoMesh(vertices, indices);
}

GeoRender::~GeoRender()
{
    SAFE_DELETE(m_canvas);
    SAFE_DELETE(m_mesh);
}

void GeoRender::Render()
{
    glViewport(m_viewPort.m_x, m_viewPort.m_y, m_viewPort.m_width, m_viewPort.m_height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_canvas->Active();
    m_mesh->Draw();
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

GeoMesh *GeoRender::GetMesh()
{
    return m_mesh;
}

void GeoRender::BindCameraUniformBlock(const Shader &shader)
{
    m_camera.BindUniformBlock(shader);
}

void GeoRender::BindLightUniformBlock(const Shader &shader)
{
    m_light.BindUniformBlock(shader);
}