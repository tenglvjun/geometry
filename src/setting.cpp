#include "setting.h"
#include "json.h"
#include "log.h"
#include <fstream>

MathConfig::MathConfig()
{
    m_pi = 0.0f;
    m_epsilon = 0.0f;
}

OpenGLConfig::OpenGLConfig()
{
    m_ambientStrength = 0.0f;
    m_specularStrength = 0.0f;
}

WindowConfig::WindowConfig()
{
    m_width = 0;
    m_height = 0;
}

SINGLETON_IMPLEMENT(GeoSetting)

GeoSetting::GeoSetting()
{
}

GeoSetting::~GeoSetting()
{
}

bool GeoSetting::Init(const std::string &filename)
{
    std::ifstream is;
    is.open(filename, std::ios::binary);

    if (!is.is_open())
    {
        std::string msg;
        msg += "open setting file ";
        msg += filename;
        msg += " failed";

        Log::GetInstance()->OutputConsole(msg);
        return false;
    }

    Json::Reader reader;
    Json::Value root;

    if (reader.parse(is, root, false))
    {
        if (root["setting"].isNull())
        {
            Log::GetInstance()->OutputConsole("invailed setting files");
            is.close();
            return false;
        }

        Json::Value setting;
        setting = root["setting"];

        if (setting["math"].isNull() || setting["opengl"].isNull() || setting["window"].isNull())
        {
            Log::GetInstance()->OutputConsole("invailed setting files");
            is.close();
            return false;
        }

        Json::Value math, opengl, window;

        math = setting["math"];
        opengl = setting["opengl"];
        window = setting["window"];

        //math node
        m_math.m_pi = math["pi"].isNull() ? math["pi"].asDouble() : 3.1415926;
        m_math.m_epsilon = math["epsilon"].isNull() ? math["epsilon"].asDouble() : 1e-7;

        //opengl
        m_openGL.m_ambientStrength = opengl["ambient strength"].isNull() ? opengl["ambient strength"].asDouble() : 0.1;
        m_openGL.m_specularStrength = opengl["specular strength"].isNull() ? opengl["specular strength"].asDouble() : 0.5;

        //window
        m_window.m_width = window["width"].isNull() ? window["width"].asInt() : 640;
        m_window.m_height = window["height"].isNull() ? window["height"].asInt() : 640;
    }

    is.close();

    return true;
}

bool GeoSetting::Save(const std::string &filename)
{
    return true;
}

MathConfig &GeoSetting::MathConfig()
{
    return m_math;
}

OpenGLConfig &GeoSetting::OpenGLConfig()
{
    return m_openGL;
}

WindowConfig &GeoSetting::WindowConfig()
{
    return m_window;
}