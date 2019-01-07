#include "global_def.h"

#if !defined(__TOOLS_HEAD_FILE__)
#define __TOOLS_HEAD_FILE__

#include <string>
#include <vector>

class Tools final
{
public:
  Tools();
  ~Tools();

public:
  SINGLETON_DECLARE(Tools)
public:
  static double Radia2Degree(const double r);
  static double Degree2Radian(const double d);
  static std::string GetLocalTime();
  static bool IsZero(const double v);
  static double Maximum(const double a, const double b);
  static double Minimum(const double a, const double b);
  static std::string ReadFile(const std::string &filePath);
  static void SplitString(const std::string &s, std::vector<std::string> &ret, const std::string &sep, const std::string &trimMark);
  static void TrimMark(std::string &s, const std::string &mark);
};

#endif // __TOOLS_HEAD_FILE__
