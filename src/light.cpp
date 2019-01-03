#include "light.h"
#include <cmath>
#include "camera.h"
#include "tools.h"
#include "setting.h"

SINGLETON_IMPLEMENT(GeoLight);

GeoLight::GeoLight()
{
    RestoreFromSetting();
}

GeoLight::GeoLight(const GeoLight &light)
{
    m_pos = light.m_pos;
    m_dir = light.m_dir;
    m_ambient = light.m_ambient;
    m_specular = light.m_specular;
    m_diffuse = light.m_diffuse;
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
    m_dir = light.m_dir;
    m_ambient = light.m_ambient;
    m_specular = light.m_specular;
    m_diffuse = light.m_diffuse;
    m_source = light.m_source;
    m_pointAttenuationRange = light.m_pointAttenuationRange;

    return *this;
}

void GeoLight::SetLight(const GeoVector3D &pos, const GeoVector3D &origin, const GeoColor &color)
{
    m_pos = pos;

    m_dir = pos - origin;
    m_dir.Normalize();
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

const unsigned int GeoLight::PointLightAttenuationRange() const
{
    return m_pointAttenuationRange;
}

void GeoLight::SetPointLightAttenuationRange(const unsigned int range)
{
    m_pointAttenuationRange = range;
}

GeoVector3D GeoLight::Ambient() const
{
    return m_ambient;
}

void GeoLight::Ambient(const GeoVector3D &ambient)
{
    m_ambient = ambient;
}

GeoVector3D GeoLight::Specular() const
{
    return m_specular;
}

void GeoLight::Specular(const GeoVector3D &specular)
{
    m_specular = specular;
}

GeoVector3D GeoLight::Diffuse() const
{
    return m_diffuse;
}

void GeoLight::Diffuse(const GeoVector3D &diffuse)
{
    m_diffuse = diffuse;
}

void GeoLight::ApplyShader(const Shader &shader) const
{
    std::vector<float> value;

    shader.SetUInt("light.source", (unsigned int)m_source);
    value.clear();
    m_ambient.Flatten(value);
    shader.SetVector("light.ambient", 3, &value[0]);
    value.clear();
    m_diffuse.Flatten(value);
    shader.SetVector("light.diffuse", 3, &value[0]);
    value.clear();
    m_specular.Flatten(value);
    shader.SetVector("light.specular", 3, &value[0]);

    value.clear();
    m_pos.Flatten(value);
    shader.SetVector("light.pos", 3, &value[0]);

    OpenGLConfig &config = GeoSetting::GetInstance()->OpenGLConfig();

    float constant = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_constant);
    float linear = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_linear);
    float quadratic = (float)(config.m_light.m_pointAttenuation[m_pointAttenuationRange].m_quadratic);

    shader.SetFloat("light.constant", constant);
    shader.SetFloat("light.linear", linear);
    shader.SetFloat("light.quadratic", quadratic);

    double cutOff = Tools::GetInstance()->Degree2dRadia(config.m_light.m_cutOff);
    double outerCutOff = Tools::GetInstance()->Degree2dRadia(config.m_light.m_outerCutOff);
    shader.SetFloat("light.cutOff", (float)cos(cutOff));
    shader.SetFloat("light.outerCutOff", (float)cos(outerCutOff));
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

    double value = config.m_light.m_ambient;
    m_ambient = GeoVector3D(value, value, value);
    value = config.m_light.m_specular;
    m_specular = GeoVector3D(value, value, value);
    value = config.m_light.m_diffuse;
    m_diffuse = GeoVector3D(value, value, value);
    m_source = config.m_light.m_source;
    m_pointAttenuationRange = config.m_light.m_pointAttenuationRange;
    m_pos = config.m_light.m_pos;
    m_dir = config.m_light.m_dir;
}