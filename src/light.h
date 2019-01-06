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

  virtual ~GeoLight();

public:
  void SetLight(const GeoVector3D &pos, const GeoVector3D &origin, const GeoColor &color);

  void SetLightSource(const LightSource_e source);
  LightSource_e GetLightSource();

  const GeoVector3D &Position() const;
  void Position(const GeoVector3D &pos);

  const GeoVector3D &Direction() const;
  void Direction(const GeoVector3D &dir);

  const unsigned int PointLightAttenuationRange() const;
  void SetPointLightAttenuationRange(const unsigned int range);

  GeoVector3D Ambient() const;
  void Ambient(const GeoVector3D &ambient);

  GeoVector3D Specular() const;
  void Specular(const GeoVector3D &specular);

  GeoVector3D Diffuse() const;
  void Diffuse(const GeoVector3D &diffuse);

  GeoColor Color() const;
  void Color(const GeoColor &color);

  unsigned int GetUniformBlockIndex() const;
  unsigned int GetUniformBindingPoint() const;
  void BindUniformBlock(Shader &shader);

public:
  SINGLETON_DECLARE(GeoLight);

protected:
  GeoColor Attanuation(const GeoVector3D &objPos, const GeoColor &color);
  void RestoreFromSetting();
  void ClearUBO();
  void UpdateProjection();
  void InitShader();
  void InitUniformBuffer();
  void UpdateUniformBuffer();

private:
  GeoLight(const GeoLight &light);
  GeoLight &operator=(const GeoLight &light);

public:
  static void InitShaderCode();
  static const std::string &GetVertexCode();
  static const std::string &GetFragmentCode();

protected:
  GeoVector3D m_pos;
  GeoVector3D m_dir;

  GeoVector3D m_ambient;
  GeoVector3D m_specular;
  GeoVector3D m_diffuse;

  GeoColor m_color;

  LightSource_e m_source;
  unsigned int m_pointAttenuationRange;

  Shader m_shader;
  unsigned int m_ubo;
  unsigned int m_bindingPoint;
};

#endif // __LIGHT_HEAD_FILE__
