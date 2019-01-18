#include "log.h"
#include "tools.h"
#include <iostream>

SINGLETON_IMPLEMENT(Log)

Log::Log()
{
    m_mapLevelMsg[Level_Info] = "Log Info: ";
    m_mapLevelMsg[Level_Warning] = "Log Warning: ";
    m_mapLevelMsg[Level_Error] = "Log Error: ";
    m_mapLevelMsg[Level_Fatal] = "Log Fatal: ";
}

Log::~Log()
{
}

void Log::OutputConsole(const std::string &msg, LogLevel_e level /* = Level_Info */)
{
    std::string now = Tools::GetInstance()->GetLocalTime();

    std::cout << now << " " << m_mapLevelMsg[level] << msg << std::endl;

    if (Level_Fatal == level)
    {
        abort();
    }
}

void Log::OutputConsole(int code, const std::string msg /* = "" */, LogLevel_e level /* = Level_Info */)
{
    std::string now = Tools::GetInstance()->GetLocalTime();

    std::cout << now << " " << m_mapLevelMsg[level] << code << " " << msg << std::endl;

    if (Level_Fatal == level)
    {
        abort();
    }
}

void Log::OutputConsole(double value, const std::string msg /* = "" */, LogLevel_e level /* = Level_Info */)
{
    std::string now = Tools::GetInstance()->GetLocalTime();

    std::cout << now << " " << m_mapLevelMsg[level] << value << " " << msg << std::endl;

    if (Level_Fatal == level)
    {
        abort();
    }
}

void Log::Dump(const GeoMatrix &matrix) const
{
    std::cout.precision(5);
    for (unsigned int i = 0; i < matrix.Rows(); i++)
    {
        for (unsigned int j = 0; j < matrix.Cols(); j++)
        {
            std::cout << matrix[i][j] << "  ";
        }

        std::cout << std::endl;
    }
}

void Log::Dump(const GeoVector &v) const
{
    for (unsigned int i = 0; i < v.Dim(); i++)
    {
        std::cout << v[i] << "    ";
    }
    std::cout << std::endl;
}

void Log::Dump(const GeoVector3D &v) const
{
    std::cout << v[0] << "    " << v[1] << "    " << v[2] << std::endl;
}

void Log::Dump(const GeoVector2D &v) const
{
    std::cout << v[0] << "    " << v[1] << std::endl;
}

void Log::Dump(const GeoVector4D &v) const
{
    std::cout << v[0] << "    " << v[1] << "    " << v[2] << "    " << v[3] << std::endl;
}

void Log::Dump(const GeoColor &c) const
{
    std::cout << "R: " << c[0] << " G: " << c[1] << " B: " << c[2] << " A: " << c[3] << std::endl;
}