#include "tools.h"
#include <time.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include "log.h"
#include "setting.h"

SINGLETON_IMPLEMENT(Tools)

Tools::Tools()
{
}
Tools::~Tools()
{
}

double Tools::Radia2Degree(const double r)
{
    MathConfig &config = GeoSetting::GetInstance()->MathConfig();

    double pi = config.m_pi;

    return r * 180 / pi;
}

double Tools::Degree2dRadia(const double d)
{
    MathConfig &config = GeoSetting::GetInstance()->MathConfig();

    double pi = config.m_pi;

    return ((d * pi) / (double)180);
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
    MathConfig &config = GeoSetting::GetInstance()->MathConfig();

    return (fabs(v) < config.m_epsilon) ? true : false;
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