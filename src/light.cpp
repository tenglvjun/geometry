#include "light.h"
#include <cmath>
#include "camera.h"
#include "tools.h"

#if !defined(DEFAULT_AMBIENT_STRENGTH)
#define DEFAULT_AMBIENT_STRENGTH 0.1
#endif // DEFAULT_AMBIENT_STRENGTH

#if !defined(DEFAULT_SPECULAR_STRENGTH)
#define DEFAULT_SPECULAR_STRENGTH 0.5
#endif // DEFAULT_SPECULAR_STRENGTH

SINGLETON_IMPLEMENT(GeoLight);

GeoLight::GeoLight()
    : m_ambientStrength(DEFAULT_AMBIENT_STRENGTH), m_specularStrength(DEFAULT_SPECULAR_STRENGTH)
{

}

GeoLight::GeoLight(const GeoVector3D& pos, const GeoVector3D& origin, const GeoColor& color)
    : m_pos(pos), m_color(color), m_ambientStrength(DEFAULT_AMBIENT_STRENGTH), m_specularStrength(DEFAULT_SPECULAR_STRENGTH)
{
    m_dir = pos - origin;
    m_dir.Normalize();
}

GeoLight::GeoLight(const GeoLight& light)
{
    m_pos = light.m_pos;
    m_color = light.m_color;
    m_dir = light.m_dir;
    m_ambientStrength = light.m_ambientStrength;
    m_specularStrength = light.m_specularStrength;
}

GeoLight::~GeoLight()
{

}

GeoLight& GeoLight::operator=(const GeoLight& light)
{
    if (&light == this) {
        return *this;
    }

    m_pos = light.m_pos;
    m_color = light.m_color;
    m_dir = light.m_dir;
    m_ambientStrength = light.m_ambientStrength;
    m_specularStrength = light.m_specularStrength;
    
    return *this;
}

void GeoLight::SetLight(const GeoVector3D& pos, const GeoVector3D& origin, const GeoColor& color)
{
    m_pos = pos;

    m_dir = pos - origin;
    m_dir.Normalize();

    m_color = color;
}

const GeoVector3D& GeoLight::Position() const
{
    return m_pos;
}

void GeoLight::Position(const GeoVector3D& pos)
{
    m_pos = pos;
}

const GeoVector3D& GeoLight::Direction() const
{
    return m_dir;
}

void GeoLight::Direction(const GeoVector3D& dir)
{
    m_dir = dir;
    m_dir.Normalize();
}

const GeoColor& GeoLight::Color() const
{
    return m_color;
}

void GeoLight::Color(const GeoColor& color)
{
    m_color = color;
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

GeoColor GeoLight::Ambient()
{
    GeoColor color = m_color;
    color.Scale(m_ambientStrength, false);

    return color;
}

GeoColor GeoLight::Diffuse(const GeoVector3D& normal, const GeoVector3D& objPos)
{
    GeoVector3D n = normal;
    n.Normalize();

    GeoVector3D lightDir = m_pos - objPos;
    lightDir.Normalize();

    GeoColor color = m_color;
    color.Scale(Tools::GetInstance()->Maximum((n % lightDir), 0.0f), false);

    return color;
}

GeoColor GeoLight::Specular(const GeoVector3D& normal, const GeoVector3D& objPos)
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

    return color;
}

GeoColor GeoLight::Illuminate(const GeoVector3D& normal, const GeoVector3D& objPos, const GeoColor& objClr)
{
    GeoColor ambient = Ambient();
    GeoColor diffuse = Diffuse(normal, objPos);
    GeoColor specular = Specular(normal, objPos);

    return (ambient + diffuse + specular) * objClr;
}