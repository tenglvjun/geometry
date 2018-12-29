#include "tools.h"
#include <time.h>
#include <cmath>
#include "setting.h"

SINGLETON_IMPLEMENT(Tools)

Tools::Tools()
{
}
Tools::~Tools()
{
}

double Tools::Radia2Degree(const  double r)
{
    MathConfig &config = GeoSetting::GetInstance()->MathConfig();

    double pi = config.m_pi;

    return r * 180 / pi;
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