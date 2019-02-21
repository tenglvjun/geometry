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
    std::string now = Tools::GetLocalTime();

    std::cout << now << " " << m_mapLevelMsg[level] << msg << std::endl;

    if (Level_Fatal == level)
    {
        abort();
    }
}

void Log::OutputConsole(int code, const std::string msg /* = "" */, LogLevel_e level /* = Level_Info */)
{
    std::string now = Tools::GetLocalTime();

    std::cout << now << " " << m_mapLevelMsg[level] << code << " " << msg << std::endl;

    if (Level_Fatal == level)
    {
        abort();
    }
}

void Log::OutputConsole(double value, const std::string msg /* = "" */, LogLevel_e level /* = Level_Info */)
{
    std::string now = Tools::GetLocalTime();

    std::cout << now << " " << m_mapLevelMsg[level] << value << " " << msg << std::endl;

    if (Level_Fatal == level)
    {
        abort();
    }
}