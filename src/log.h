#if !defined(__LOG_HEAD_FILE__)
#define __LOG_HEAD_FILE__

#include "global_def.h"
#include "global_enum.h"
#include <string>
#include <map>
#include "matrix.h"
#include "vector.h"

class Log final
{
public:
  SINGLETON_DECLARE(Log)

public:
  Log();
  ~Log();

public:
  void OutputConsole(const std::string &msg, LogLevel_e level = Level_Info);
  void OutputConsole(int code, const std::string msg = "", LogLevel_e level = Level_Info);
  void OutputConsole(double value, const std::string msg = "", LogLevel_e level = Level_Info);

public:
  void Dump(const GeoMatrix &matrix);
  void Dump(const GeoVector &v);
  void Dump(const GeoVector3D &v);
  void Dump(const GeoVector2D &v);
  void Dump(const GeoVector4D &v);

private:
  std::map<LogLevel_e, std::string> m_mapLevelMsg;
  std::string m_filename;
};

#endif // __LOG_HEAD_FILE__
