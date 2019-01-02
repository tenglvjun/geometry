#include "light.h"
#include <cmath>
#include "camera.h"
#include "tools.h"
#include "setting.h"
#include "log.h"

std::string GeoLight::m_shaderFragmentCode = "";

SINGLETON_IMPLEMENT(GeoLight);

GeoLight::GeoLight()
{
    RestoreFromSetting();
    GeoLight::InitShaderCode();
}

GeoLight::GeoLight(const GeoVector3D &pos, const GeoVector3D &origin, const GeoColor &color)
    : m_pos(pos), m_color(color)
{
    m_dir = pos - origin;
    m_dir.Normalize();

    RestoreFromSetting();
    GeoLight::InitShaderCode();
}

GeoLight::GeoLight(const GeoLight &light)
{
    m_pos = light.m_pos;
    m_color = light.m_color;
    m_dir = light.m_dir;
    m_ambientStrength = light.m_ambientStrength;
    m_specularStrength = light.m_specularStrength;
    m_source = light.m_source;
    m_pointAttenuationRange = light.m_pointAttenuationRange;
}

GeoLight::~GeoLight()
{
}

GeoLight &GeoLight::operator=(const GeoLight &light)
{
    if (&light == this)
    {
        return *this;
    }

    m_pos = light.m_pos;
    m_color = light.m_color;
    m_dir = light.m_dir;
    m_ambientStrength = light.m_ambientStrength;
    m_specularStrength = light.m_specularStrength;
    m_source = light.m_source;
    m_pointAttenuationRange = light.m_pointAttenuationRange;

    return *this;
}

void GeoLight::SetLight(const GeoVector3D &pos, const GeoVector3D &origin, const GeoColor &color, const LightSource_e source)
{
    m_pos = pos;

    m_dir = pos - origin;
    m_dir.Normalize();

    m_color = color;
    m_source = source;
}

void GeoLight::SetLightSource(const LightSource_e source)
{
    m_source = source;
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
}

const GeoVector3D &GeoLight::Direction() const
{
    return m_dir;
}

void GeoLight::Direction(const GeoVector3D &dir)
{
    m_dir = dir;
    m_dir.Normalize();
}

const GeoColor &GeoLight::Color() const
{
    return m_color;
}

void GeoLight::Color(const GeoColor &color)
{
    m_color = color;
}

const unsigned int GeoLight::PointLightAttenuationRange() const
{
    return m_pointAttenuationRange;
}

void GeoLight::SetPointLightAttenuationRange(const unsigned int range)
{
    m_pointAttenuationRange = range;
}

double GeoLight::AmbientStrength() const
{
    return m_ambientStrength;
}

void GeoLight::AmbientStrength(const double ambientStrength)
{
    m_ambientStrength = ambientStrength;
}

double GeoLight::SpecularStrength() const
{
    return m_specularStrength;
}

void GeoLight::SpecularStrength(const double specularStrength)
{
    m_specularStrength = specularStrength;
}

GeoColor GeoLight::Ambient(const GeoVector3D &objPos)
{
    GeoColor color = m_color;
    color.Scale(m_ambientStrength, false);

    return Attanuation(objPos, color);
}

GeoColor GeoLight::Diffuse(const GeoVector3D &normal, const GeoVector3D &objPos)
{
    GeoVector3D n = normal;
    n.Normalize();

    GeoVector3D lightDir = m_pos - objPos;
    lightDir.Normalize();

    GeoColor color = m_color;
    color.Scale(Tools::GetInstance()->Maximum((n % lightDir), 0.0f), false);

    return Attanuation(objPos, color);
}

GeoColor GeoLight::Specular(const GeoVector3D &normal, const GeoVector3D &objPos)
{
    GeoVector3D n = normal;
    n.Normalize();

    GeoVector3D viewDir = GeoCamera::GetInstance()->Position() - objPos;
    viewDir.Normalize();

    GeoVector3D reflectDir = n * (n % m_dir) * 2 - m_dir;
    reflectDir.Normalize();

    double spec = pow(Tools::GetInstance()->Maximum((viewDir % reflectDir), 0.0), 32);

    GeoColor color = m_color;
    color.Scale(m_specularStrength * spec, false);

    return Attanuation(objPos, color);
}

GeoColor GeoLight::Illuminate(const GeoVector3D &normal, const GeoVector3D &objPos, const GeoColor &objClr)
{
    GeoColor ambient = Ambient(objPos);
    GeoColor diffuse = Diffuse(normal, objPos);
    GeoColor specular = Specular(normal, objPos);

    return (ambient + diffuse + specular) * objClr;
}

void GeoLight::ApplyShader(const Shader &shader) const
{
    std::vector<float> value;

    shader.SetUInt("light.source", (unsigned int)m_source);
    shader.SetFloat("light.ambientStrength", (float)m_ambientStrength);
    shader.SetFloat("light.specularStrength", (float)m_specularStrength);

    value.clear();
    m_pos.Flatten(value);
    shader.SetVector("light.pos", 3, &value[0]);

    if (m_source == POINT_LIGHT)
    {
        OpenGLConfig &config = GeoSetting::GetInstance()->OpenGLConfig();

        float constant = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_constant);
        float linear = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_linear);
        float quadratic = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_quadratic);

        shader.SetFloat("pointLightAttenuation.constant", constant);
        shader.SetFloat("pointLightAttenuation.linear", linear);
        shader.SetFloat("pointLightAttenuation.quadratic", quadratic);
    }
}

GeoColor GeoLight::Attanuation(const GeoVector3D &objPos, const GeoColor &color)
{
    GeoColor c = color;

    if (m_source != POINT_LIGHT)
    {
        return c;
    }

    OpenGLConfig &config = GeoSetting::GetInstance()->OpenGLConfig();

    float constant = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_constant);
    float linear = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_linear);
    float quadratic = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_quadratic);

    double distance = (m_pos - objPos).Magnitude();
    double attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
    c.Scale(attenuation, false);

    return c;
}

void GeoLight::RestoreFromSetting()
{
    OpenGLConfig &config = GeoSetting::GetInstance()->OpenGLConfig();
    m_ambientStrength = config.m_light.m_ambientStrength;
    m_specularStrength = config.m_light.m_specularStrength;
    m_source = config.m_light.m_source;
    m_pointAttenuationRange = config.m_light.m_pointAttenuationRange;
}

void GeoLight::InitShaderCode()
{
    m_shaderFragmentCode = Tools::ReadFile("shader/fragment/light.fs");
}

const std::string& GeoLight::GetFragmentCode()
{
    return m_shaderFragmentCode;
}
