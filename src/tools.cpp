#include "tools.h"
#include <time.h>
#include <cmath>

SINGLETON_IMPLEMENT(Tools)

Tools::Tools()
{
}
Tools::~Tools()
{
}

double Tools::Radia2Degree(const  double r)
{
    double pi = PI;

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