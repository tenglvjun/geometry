#if !defined(__MATERIAL_HEAD_FILE__)
#define __MATERIAL_HEAD_FILE__

#include "vector.h"
#include "shader.h"

class GeoMaterial
{
  public:
    GeoMaterial();
    GeoMaterial(const GeoVector3D &ambient, const GeoVector3D &diffuse, const GeoVector3D &specular, const double shininess);
    GeoMaterial(const GeoMaterial &material);
    virtual ~GeoMaterial();

  public:
    GeoMaterial &operator=(const GeoMaterial &material);

  public:
    GeoVector3D Ambient() const;
    void Ambient(const GeoVector3D &ambient);

    GeoVector3D Specular() const;
    void Specular(const GeoVector3D &specular);

    GeoVector3D Diffuse() const;
    void Diffuse(const GeoVector3D &diffuse);

    double Shininess() const;
    void Shininess(const double shininess);

    void ApplyShader(const Shader &shader) const;

  protected:
    GeoVector3D m_ambient;
    GeoVector3D m_diffuse;
    GeoVector3D m_specular;
    double m_shininess;
};

#endif // __MATERIAL_HEAD_FILE__
