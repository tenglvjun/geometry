#include "material.h"


GeoMaterial::GeoMaterial()
    : m_ambient(1.0f, 1.0f, 1.0f), m_diffuse(1.0f, 1.0f, 1.0f), m_specular(1.0f, 1.0f, 1.0f), m_shininess(1.0f)
{

}

GeoMaterial::GeoMaterial(const GeoVector3D& ambient, const GeoVector3D& diffuse, const GeoVector3D& specular, const double shininess)
    : m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess)
{

}

GeoMaterial::GeoMaterial(const GeoMaterial& material)
{
    m_ambient = material.m_ambient;
    m_diffuse = material.m_diffuse;
    m_specular = material.m_specular;    
    m_shininess = material.m_shininess;
}

GeoMaterial::~GeoMaterial()
{

}

GeoMaterial& GeoMaterial::operator=(const GeoMaterial& material)
{
    if (&material == this) {
        return *this;
    }

    m_ambient = material.m_ambient;
    m_diffuse = material.m_diffuse;
    m_specular = material.m_specular;    
    m_shininess = material.m_shininess;

    return *this;
    
}

GeoVector3D GeoMaterial::Ambient() const
{
    return m_ambient;
}

void GeoMaterial::Ambient(const GeoVector3D &ambient)
{
    m_ambient = ambient;
}

GeoVector3D GeoMaterial::Specular() const
{
    return m_specular;
}

void GeoMaterial::Specular(const GeoVector3D &specular)
{
    m_specular = specular;
}

GeoVector3D GeoMaterial::Diffuse() const
{
    return m_diffuse;
}

void GeoMaterial::Diffuse(const GeoVector3D &diffuse)
{
    m_diffuse = diffuse;
}

double GeoMaterial::Shininess() const
{
    return m_shininess;
}

void GeoMaterial::Shininess(const double shininess)
{
    m_shininess = shininess;
}

void GeoMaterial::ApplyShader(const Shader &shader) const
{
    std::vector<float> value;

    m_ambient.Flatten(value);
    shader.SetVector("material.ambient", 3, &value[0]);

    value.clear();
    m_diffuse.Flatten(value);
    shader.SetVector("material.diffuse", 3, &value[0]);

    value.clear();
    m_specular.Flatten(value);
    shader.SetVector("material.specular", 3, &value[0]);

    shader.SetFloat("material.shininess", (float)m_shininess);
}