#if !defined(__SETTING_HEAD_FILE__)
#define __SETTING_HEAD_FILE__

#include <string>
#include "global_def.h"
#include "global_enum.h"
#include "json.h"

struct MathConfig
{
  MathConfig();

  double m_pi;
  double m_epsilon;
};

struct OpenGLConfig
{
  OpenGLConfig();

  double m_ambientStrength;
  double m_specularStrength;
  LightSource_e m_source;
};

struct WindowConfig
{
  WindowConfig();

  int m_width;
  int m_height;
};

class GeoSetting final
{
public:
  GeoSetting();
  ~GeoSetting();

public:
  bool Init(const std::string &filename);
  bool Save(const std::string &filename);

  MathConfig &MathConfig();
  OpenGLConfig &OpenGLConfig();
  WindowConfig &WindowConfig();

public:
  SINGLETON_DECLARE(GeoSetting)

protected:
  void ParseMath(const Json::Value &math);
  void ParseOpenGL(const Json::Value &openGL);
  void ParseWindow(const Json::Value &window);

private:
  GeoSetting(const GeoSetting &setting);
  GeoSetting &operator=(const GeoSetting &setting);

private:
  struct MathConfig m_math;
  struct OpenGLConfig m_openGL;
  struct WindowConfig m_window;
};

#endif // __SETTING_HEAD_FILE__
