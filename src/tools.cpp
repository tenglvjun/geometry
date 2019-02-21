#include "tools.h"
#include <time.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include "log.h"
#include "setting.h"
#include "math_def.h"

SINGLETON_IMPLEMENT(Tools)

Tools::Tools()
{
}
Tools::~Tools()
{
}

double Tools::Radia2Degree(const double r)
{
    return r * 180 / PI;
}

double Tools::Degree2Radian(const double d)
{
    return ((d * PI) / (double)180);
}

std::string Tools::GetLocalTime()
{
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));

    return tmp;
}

bool Tools::IsZero(const double v)
{
    return (fabs(v) < EPSILON) ? true : false;
}

double Tools::Maximum(const double a, const double b)
{
    return (a > b) ? a : b;
}

double Tools::Minimum(const double a, const double b)
{
    return (a < b) ? a : b;
}

std::string Tools::ReadFile(const std::string &filePath)
{
    std::string content;

    std::ifstream file;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        file.open(filePath);
        std::stringstream stream;
        // read file's buffer contents into streams
        stream << file.rdbuf();
        // close file handlers
        file.close();
        // convert stream into string
        content = stream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::string error = "open file failed, file path is ";
        error += filePath;
        Log::GetInstance()->OutputConsole(error, Level_Fatal);
    }

    return content;
}

void Tools::SplitString(const std::string &s, std::vector<std::string> &ret, const std::string &sep, const std::string &trimMark)
{
    if (s.empty())
    {
        return;
    }

    std::string str = s;

    if (!trimMark.empty())
    {
        TrimMark(str, trimMark);
    }

    unsigned int size = (unsigned int)sep.size();
    unsigned int length = 0;
    while (!str.empty())
    {
        std::string::size_type pos = str.find(sep);
        if (pos == std::string::npos)
        {
            ret.push_back(str);
            length = (unsigned int)str.length();
        }
        else
        {
            ret.push_back(str.substr(0, pos));
            length = (unsigned int)(pos + size);
        }

        str.erase(0, length);
    }
}

void Tools::TrimMark(std::string &s, const std::string &mark)
{
    unsigned int size = (unsigned int)mark.size();
    while (true)
    {
        std::string::size_type pos = s.find(mark);
        if (pos == std::string::npos)
        {
            break;
        }

        s.erase(pos, size);
    }
}