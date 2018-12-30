#include "setting.h"
#include "log.h"
#include <fstream>

MathConfig::MathConfig()
{
    m_pi = 0.0f;
    m_epsilon = 0.0f;
}

PointLightAttenuation::PointLightAttenuation()
{
    m_constant = 0.0f;
    m_linear = 0.0f;
    m_quadratic = 0.0f;
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

        ParseMath(math);
        ParseOpenGL(opengl);
        ParseWindow(window);
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

void GeoSetting::ParseMath(const Json::Value &math)
{
    Json::Value pi, epsilon;

    m_math.m_pi = !math["pi"].isNull() ? 3.1415926 : math["pi"].asDouble();
    m_math.m_epsilon = math["epsilon"].isNull() ? 1e-7 : math["epsilon"].asDouble();
}

void GeoSetting::ParseOpenGL(const Json::Value &openGL)
{
    Json::Value ambientStrength, specularStrength;
    Json::Value source;
    Json::Value attenuationArray;

    m_openGL.m_ambientStrength = openGL["ambient strength"].isNull() ? 0.1 : openGL["ambient strength"].asDouble();
    m_openGL.m_specularStrength = openGL["specular strength"].isNull() ? 0.5 : openGL["specular strength"].asDouble();
    m_openGL.m_source = openGL["light source"].isNull() ? DIRECTION_LIGHT : (LightSource_e)(openGL["light source"].asInt());

    if (openGL["point light attenuation"].isNull())
    {
        Log::GetInstance()->OutputConsole("point light attenuation's information is missed");
        assert(0);
        return;
    }

    attenuationArray = openGL["point light attenuation"];

    unsigned int range;

    for (unsigned int i = 0; i < attenuationArray.size(); i++)
    {
        Json::Value attenuation = attenuationArray[i];

        PointLightAttenuation pla;

        range = attenuation["range"].asUInt();
        pla.m_constant = attenuation["constant"].asDouble();
        pla.m_linear = attenuation["linear"].asDouble();
        pla.m_quadratic = attenuation["quadratic"].asDouble();

        m_openGL.m_pointAttenuation[range] = pla;
    }
}

void GeoSetting::ParseWindow(const Json::Value &window)
{
    Json::Value width, height;

    m_window.m_width = window["width"].isNull() ? 640 : window["width"].asInt();
    m_window.m_height = window["height"].isNull() ? 640 : window["height"].asInt();
}