#if !defined(__LIGHT_HEAD_FILE__)
#define __LIGHT_HEAD_FILE__

#include "vector.h"
#include "color.h"
#include "global_def.h"

class GeoLight
{
  public:
    GeoLight();
    GeoLight(const GeoVector3D &pos, const GeoVector3D &origin, const GeoColor &color);
    GeoLight(const GeoLight &light);
    virtual ~GeoLight();

  public:
    GeoLight &operator=(const GeoLight &light);

  public:
    void SetLight(const GeoVector3D &pos, const GeoVector3D &origin, const GeoColor &color);

    const GeoVector3D &Position() const;
    void Position(const GeoVector3D &pos);

    const GeoVector3D &Direction() const;
    void Direction(const GeoVector3D &dir);

    const GeoColor &Color() const;
    void Color(const GeoColor &color);

    double AmbientStrength() const;
    void AmbientStrength(const double ambientStrength);

    double SpecularStrength() const;
    void SpecularStrength(const double specularStrength);

    GeoColor Ambient();
    GeoColor Diffuse(const GeoVector3D &normal, const GeoVector3D &objPos);
    GeoColor Specular(const GeoVector3D &normal, const GeoVector3D &objPos);

    GeoColor Illuminate(const GeoVector3D &normal, const GeoVector3D &objPos, const GeoColor &objClr);

  public:
    SINGLETON_DECLARE(GeoLight);

  protected:
    GeoVector3D m_pos;
    GeoVector3D m_dir;
    GeoColor m_color;

    double m_ambientStrength;
    double m_specularStrength;
};

#endif // __LIGHT_HEAD_FILE__
