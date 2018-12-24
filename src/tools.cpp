#include "tools.h"
#include <time.h>
#include <math.h>

SINGLETON_IMPLEMENT(Tools)

Tools::Tools()
{
}
Tools::~Tools()
{
}

double Tools::Radia2Degree(double r)
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

bool Tools::IsZero(double v)
{
    return (fabs(v) < EPSILON) ? true : false;
}