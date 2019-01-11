#include "camera.h"
#include "tools.h"
#include "shader_code_manage.h"
#include <vector>
#include "opengl_helper.h"
#include <iostream>

GeoFrustum::GeoFrustum()
{
    m_left = m_right = m_top = m_bottom = m_near = m_far = 0.0f;
}

GeoFrustum::GeoFrustum(const double l, const double r, const double b, const double t, const double n, const double f)
{
    m_left = l;
    m_right = r;
    m_top = t;
    m_bottom = b;
    m_near = n;
    m_far = f;
}

SINGLETON_IMPLEMENT(GeoCamera);

GeoCamera::GeoCamera()
    : m_view(4, 4), m_projection(4, 4), m_sensitivity(0.1f), m_projType(PT_Invalid), m_ubo(0)
{
    m_view.SetIdentity();
    m_projection.SetIdentity();
    m_bindingPoint = GeoOpenGLHelper::GetInstance()->RequestBindingPoint();

    InitShader();
    InitUniformBuffer();
    UpdateUniformBuffer();
}

GeoCamera::~GeoCamera()
{
    ClearUBO();
}

void GeoCamera::ResetCamera(const GeoVector3D &pos, const GeoVector3D &center, const GeoVector3D &up)
{
    m_pos = pos;
    m_center = center;
    m_up = up;

    m_front = m_center - m_pos;
    m_front.Normalize();

    m_side = m_front * m_up;
    m_side.Normalize();

    m_upOrtho = m_side * m_front;

    m_view.SetIdentity();

    GeoMatrix m1(4, 4);
    m1.SetIdentity();
    m1[0][0] = m_side[0];
    m1[0][1] = m_side[1];
    m1[0][2] = m_side[2];
    m1[1][0] = m_upOrtho[0];
    m1[1][1] = m_upOrtho[1];
    m1[1][2] = m_upOrtho[2];
    m1[2][0] = -m_front[0];
    m1[2][1] = -m_front[1];
    m1[2][2] = -m_front[2];

    GeoMatrix m2(4, 4);
    m2.SetIdentity();
    m2[0][3] = -m_pos[0];
    m2[1][3] = -m_pos[1];
    m2[2][3] = -m_pos[2];

    m_view = m1 * m2;
}

void GeoCamera::SetFrustum(const GeoFrustum &frustum, ProjType_e pt)
{
    m_frustum = frustum;
    m_projType = pt;

    UpdateProjection();
}

const GeoMatrix &GeoCamera::GetViewMatrix() const
{
    return m_view;
}

const GeoMatrix &GeoCamera::GetProjectionMatrix() const
{
    return m_projection;
}

void GeoCamera::Move(const GeoVector3D &v)
{
    m_view[0][3] += v[0];
    m_view[1][3] += v[1];
    m_view[2][3] += v[2];

    UpdateUniformBuffer();
}

void GeoCamera::Rotate(const GeoMatrix &m)
{
    GeoMatrix subMatrix = m_view.SubMatrix(0, 3, 0, 3);
    subMatrix = m * subMatrix;

    m_view.Replace(0, 0, subMatrix);

    UpdateUniformBuffer();
}

void GeoCamera::Scale(bool enlarge)
{
    m_frustum.m_near += (enlarge ? (m_sensitivity) : (-m_sensitivity));

    UpdateProjection();
}

const GeoVector3D &GeoCamera::Position() const
{
    return m_pos;
}

unsigned int GeoCamera::GetUniformBlockIndex() const
{
    return m_shader.GetUniformBlockIndex("CameraBlock");
}

unsigned int GeoCamera::GetUniformBindingPoint() const
{
    return m_bindingPoint;
}

void GeoCamera::BindUniformBlock(Shader &shader)
{
    shader.BindUniformBlock("CameraBlock", m_bindingPoint);
}

void GeoCamera::ClearUBO()
{
    if (m_ubo > 0)
    {
        glDeleteBuffers(1, &m_ubo);
        m_ubo = 0;
    }
}

void GeoCamera::UpdateProjection()
{
    switch (m_projType)
    {
    case PT_Persp:
    {
        m_projection.SetIdentity();
        m_projection[0][0] = 2 * m_frustum.m_near / (m_frustum.m_right - m_frustum.m_left);
        m_projection[0][2] = (m_frustum.m_right + m_frustum.m_left) / (m_frustum.m_right - m_frustum.m_left);
        m_projection[1][1] = 2 * m_frustum.m_near / (m_frustum.m_top - m_frustum.m_bottom);
        m_projection[1][2] = (m_frustum.m_top + m_frustum.m_bottom) / (m_frustum.m_top - m_frustum.m_bottom);
        m_projection[2][2] = -((m_frustum.m_far + m_frustum.m_near) / (m_frustum.m_far - m_frustum.m_near));
        m_projection[2][3] = -((2 * m_frustum.m_near * m_frustum.m_far) / (m_frustum.m_far - m_frustum.m_near));
        m_projection[3][2] = -1;
        m_projection[3][3] = 0;

        break;
    }
    case PT_Persp_Infinite:
    {
        m_projection.SetIdentity();
        m_projection[0][0] = 2 * m_frustum.m_near / (m_frustum.m_right - m_frustum.m_left);
        m_projection[0][2] = (m_frustum.m_right + m_frustum.m_left) / (m_frustum.m_right - m_frustum.m_left);
        m_projection[1][1] = 2 * m_frustum.m_near / (m_frustum.m_top - m_frustum.m_bottom);
        m_projection[1][2] = (m_frustum.m_top + m_frustum.m_bottom) / (m_frustum.m_top - m_frustum.m_bottom);
        m_projection[2][2] = -1;
        m_projection[2][3] = -2 * m_frustum.m_near;
        m_projection[3][2] = -1;
        m_projection[3][3] = 0;

        break;
    }
    case PT_Ortho:
    {
        m_projection.SetIdentity();
        m_projection[0][0] = 2 / (m_frustum.m_right - m_frustum.m_left);
        m_projection[0][3] = -(m_frustum.m_right + m_frustum.m_left) / (m_frustum.m_right - m_frustum.m_left);
        m_projection[1][1] = 2 / (m_frustum.m_top - m_frustum.m_bottom);
        m_projection[1][3] = -(m_frustum.m_top + m_frustum.m_bottom) / (m_frustum.m_top - m_frustum.m_bottom);
        m_projection[2][2] = -2 / (m_frustum.m_far - m_frustum.m_near);
        m_projection[2][3] = -(m_frustum.m_near + m_frustum.m_far) / (m_frustum.m_far - m_frustum.m_near);

        break;
    }
    default:
        break;
    }

    UpdateUniformBuffer();
}

void GeoCamera::InitShader()
{
    const GeoShaderCode &cameraCode = GeoShaderCodeMgr::GetInstance()->GetShaderCode(SCT_Camera);
    
    m_shader.Init(cameraCode.m_vertex, cameraCode.m_fragment);
    m_shader.Complie();
}

void GeoCamera::InitUniformBuffer()
{
    ClearUBO();

    int size = m_shader.GetUniformBlockSize("CameraBlock");

    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, m_bindingPoint, m_ubo, 0, size);
}

void GeoCamera::UpdateUniformBuffer()
{
    std::vector<float> data;
    m_view.Flatten(data);
    m_projection.Flatten(data);
    m_pos.Flatten(data);

    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float) * data.size(), &data[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}