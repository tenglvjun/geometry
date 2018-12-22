#if !defined(__LOG_HEAD_FILE__)
#define __LOG_HEAD_FILE__

#include "global_def.h"
#include <string>
#include <map>

typedef enum LogLevel
{
  Level_Info = 0,
  Level_Warning,
  Level_Error,
  Level_Fatal,
} LogLevel_e;

class Log final
{
public:
  SINGLETON_DECLARE(Log)

public:
  Log();
  virtual ~Log();

public:
  void OutputConsole(const std::string &msg, LogLevel_e level = Level_Info);
  void OutputConsole(int code, const std::string &msg, LogLevel_e level = Level_Info);

private:
  std::map<LogLevel_e, std::string> m_mapLevelMsg;
  std::string m_filename;
};

#endif // __LOG_HEAD_FILE__
