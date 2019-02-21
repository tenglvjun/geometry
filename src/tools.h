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
  static std::string GetLocalTime();
  static double Maximum(const double a, const double b);
  static double Minimum(const double a, const double b);
  static std::string ReadFile(const std::string &filePath);
  static void SplitString(const std::string &s, std::vector<std::string> &ret, const std::string &sep, const std::string &trimMark);
  static void TrimMark(std::string &s, const std::string &mark);
};

#endif // __TOOLS_HEAD_FILE__
