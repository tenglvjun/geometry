#include "global_def.h"

#if !defined(__TOOLS_HEAD_FILE__)
#define __TOOLS_HEAD_FILE__

#include <string>

class Tools final
{
  public:
    Tools();
    ~Tools();

  public:
    SINGLETON_DECLARE(Tools)
  public:
    static double Radia2Degree(double r);
    static std::string GetLocalTime();
    static bool IsZero(double v);
};

#endif // __TOOLS_HEAD_FILE__
