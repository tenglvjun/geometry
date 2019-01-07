#include "light.h"
#include <cmath>
#include "camera.h"
#include "tools.h"
#include "setting.h"
#include "opengl_helper.h"
#include "shader_code_manage.h"
#include <iostream>

SINGLETON_IMPLEMENT(GeoLight);

GeoLight::GeoLight()
    : m_ubo(0)
{
    RestoreFromSetting();

    m_bindingPoint = GeoOpenGLHelper::GetInstance()->RequestBindingPoint();

    InitShader();
    InitUniformBuffer();
    UpdateUniformBuffer();
}

GeoLight::~GeoLight()
{
    ClearUBO();
}

void GeoLight::SetLight(const GeoVector3D &pos, const GeoVector3D &origin, const GeoColor &color)
{
    m_pos = pos;

    m_color = color;

    UpdateUniformBuffer();
}

void GeoLight::SetLightSource(const LightSource_e source)
{
    m_source = source;

    UpdateUniformBuffer();
}

LightSource_e GeoLight::GetLightSource()
{
    return m_source;
}

const GeoVector3D &GeoLight::Position() const
{
    return m_pos;
}

void GeoLight::Position(const GeoVector3D &pos)
{
    m_pos = pos;

    UpdateUniformBuffer();
}

GeoVector3D GeoLight::Direction() const
{
    GeoVector3D dir = GeoVector3D(0.0f, 0.0f, 0.0f) - m_pos;
    dir.Normalize();
    return dir;
}

const unsigned int GeoLight::PointLightAttenuationRange() const
{
    return m_pointAttenuationRange;
}

void GeoLight::SetPointLightAttenuationRange(const unsigned int range)
{
    m_pointAttenuationRange = range;

    UpdateUniformBuffer();
}

GeoVector3D GeoLight::Ambient() const
{
    return m_ambient;
}

void GeoLight::Ambient(const GeoVector3D &ambient)
{
    m_ambient = ambient;

    UpdateUniformBuffer();
}

GeoVector3D GeoLight::Specular() const
{
    return m_specular;
}

void GeoLight::Specular(const GeoVector3D &specular)
{
    m_specular = specular;

    UpdateUniformBuffer();
}

GeoVector3D GeoLight::Diffuse() const
{
    return m_diffuse;
}

void GeoLight::Diffuse(const GeoVector3D &diffuse)
{
    m_diffuse = diffuse;

    UpdateUniformBuffer();
}

GeoColor GeoLight::Color() const
{
    return m_color;
}

void GeoLight::Color(const GeoColor &color)
{
    m_color = color;

    UpdateUniformBuffer();
}

unsigned int GeoLight::GetUniformBlockIndex() const
{
    return m_shader.GetUniformBlockIndex("LightBlock");
}

unsigned int GeoLight::GetUniformBindingPoint() const
{
    return m_bindingPoint;
}

void GeoLight::BindUniformBlock(Shader &shader)
{
    shader.BindUniformBlock("LightBlock", m_bindingPoint);
}

void GeoLight::ClearUBO()
{
    if (m_ubo > 0)
    {
        glDeleteBuffers(1, &m_ubo);
        m_ubo = 0;
    }
}

void GeoLight::RestoreFromSetting()
{
    OpenGLConfig &config = GeoSetting::GetInstance()->OpenGLConfig();

    m_ambient = config.m_light.m_ambient;
    m_specular = config.m_light.m_specular;
    m_diffuse = config.m_light.m_diffuse;
    m_source = config.m_light.m_source;
    m_pointAttenuationRange = config.m_light.m_pointAttenuationRange;
    m_pos = config.m_light.m_pos;
    m_color = config.m_light.m_color;
}

void GeoLight::InitShader()
{
    const GeoShaderCode &shaderCode = GeoShaderCodeMgr::GetInstance()->GetShaderCode(SCT_Light);

    std::vector<std::string> vert;
    std::vector<std::string> frag;

    vert.push_back(shaderCode.m_fragment);

    m_shader.SetShaderCodes(vert, frag);
    m_shader.Complie();
}

void GeoLight::InitUniformBuffer()
{
    ClearUBO();

    std::vector<float> data;
    m_pos.Flatten(data);
    m_ambient.Flatten(data);
    m_diffuse.Flatten(data);
    m_specular.Flatten(data);
    m_color.Flatten(data);

    int size = m_shader.GetUniformBlockSize("LightBlock");

    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, m_bindingPoint, m_ubo, 0, size);
}

void GeoLight::UpdateUniformBuffer()
{
    OpenGLConfig &config = GeoSetting::GetInstance()->OpenGLConfig();

    float constant = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_constant);
    float linear = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_linear);
    float quadratic = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_quadratic);

    float cutOff = (float)(Tools::GetInstance()->Degree2Radian(config.m_light.m_cutOff));
    float outerCutOff = (float)(Tools::GetInstance()->Degree2Radian(config.m_light.m_outerCutOff));

    cutOff = cos(cutOff);
    outerCutOff = cos(outerCutOff);

    unsigned int offset = 0;

    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(int), &m_source);

    std::vector<float> data;
    m_pos.Flatten(data);
    offset = 16;
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float) * data.size(), &data[0]);

    data.clear();
    m_ambient.Flatten(data);
    offset = 32;
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float) * data.size(), &data[0]);

    data.clear();
    m_diffuse.Flatten(data);
    offset = 48;
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float) * data.size(), &data[0]);

    data.clear();
    m_specular.Flatten(data);
    offset = 64;
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float) * data.size(), &data[0]);

    data.clear();
    m_color.Flatten(data);
    offset = 80;
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float) * data.size(), &data[0]);

    offset = 96;
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float), &constant);
    offset = 100;
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float), &linear);
    offset = 104;
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float), &quadratic);
    offset = 108;
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float), &cutOff);
    offset = 112;
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float), &outerCutOff);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}