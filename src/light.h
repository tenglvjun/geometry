#if !defined(__LIGHT_HEAD_FILE__)
#define __LIGHT_HEAD_FILE__

#include "vector.h"
#include "color.h"
#include "global_def.h"
#include "global_enum.h"
#include "shader.h"

class GeoLight final
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

  void SetLightSource(const LightSource_e source);
  LightSource_e GetLightSource();

  const GeoVector3D &Position() const;
  void Position(const GeoVector3D &pos);

  const GeoVector3D &Direction() const;
  void Direction(const GeoVector3D &dir);

  const GeoColor &Color() const;
  void Color(const GeoColor &color);

  const unsigned int PointLightAttenuationRange() const;
  void SetPointLightAttenuationRange(const unsigned int range);

  GeoVector3D AmbientStrength() const;
  void AmbientStrength(const GeoVector3D &ambientStrength);

  GeoVector3D SpecularStrength() const;
  void SpecularStrength(const GeoVector3D &specularStrength);

  GeoVector3D DiffuseStrength() const;
  void DiffuseStrength(const GeoVector3D &diffuseStrength);

  void ApplyShader(const Shader &shader) const;

public:
  SINGLETON_DECLARE(GeoLight);

protected:
  GeoColor Attanuation(const GeoVector3D &objPos, const GeoColor &color);
  void RestoreFromSetting();

public:
  static void InitShaderCode();
  static const std::string &GetVertexCode();
  static const std::string &GetFragmentCode();

protected:
  GeoVector3D m_pos;
  GeoVector3D m_dir;
  GeoColor m_color;

  GeoVector3D m_ambientStrength;
  GeoVector3D m_specularStrength;
  GeoVector3D m_diffuseStrength;

  LightSource_e m_source;
  unsigned int m_pointAttenuationRange;
};

#endif // __LIGHT_HEAD_FILE__
