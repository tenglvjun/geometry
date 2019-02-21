#include "setting.h"
#include "log.h"
#include <fstream>
#include <assert.h>
#include "tools.h"
#include <vector>

PointLightAttenuation::PointLightAttenuation()
{
    m_constant = 0.0f;
    m_linear = 0.0f;
    m_quadratic = 0.0f;
}

LightConfig::LightConfig()
{
    m_source = DIRECTION_LIGHT;
    m_pointAttenuationRange = 0;
    m_ambient = GeoVector3D(0.0f, 0.0f, 0.0f);
    m_diffuse = GeoVector3D(0.0f, 0.0f, 0.0f);
    m_specular = GeoVector3D(0.0f, 0.0f, 0.0f);
}

OpenGLConfig::OpenGLConfig()
{
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

        Json::Value opengl, window;

        opengl = setting["opengl"];
        window = setting["window"];

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

OpenGLConfig &GeoSetting::OpenGLConfig()
{
    return m_openGL;
}

WindowConfig &GeoSetting::WindowConfig()
{
    return m_window;
}

void GeoSetting::ParseOpenGL(const Json::Value &openGL)
{
    if (openGL["light"].isNull())
    {
        Log::GetInstance()->OutputConsole("light information is missed");
        assert(0);
        return;
    }

    Json::Value light = openGL["light"];

    if (light["position"].isNull())
    {
        Log::GetInstance()->OutputConsole("light position information is missed");
        m_openGL.m_light.m_pos = GeoVector3D(0.0f, 0.0f, 0.0f);
    }
    else
    {
        std::string pos = light["position"].asString();
        std::vector<std::string> ret;

        Tools::GetInstance()->SplitString(pos, ret, ",", " ");

        assert(ret.size() == GeoVector3D::Size());
        
        double x, y, z;
        x = atof(ret[0].c_str());
        y = atof(ret[1].c_str());
        z = atof(ret[2].c_str());

        m_openGL.m_light.m_pos = GeoVector3D(x, y, z);
    }

    if (light["color"].isNull())
    {
        Log::GetInstance()->OutputConsole("light color information is missed");
        m_openGL.m_light.m_color = GeoColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else
    {
        std::string color = light["color"].asString();
        std::vector<std::string> ret;

        Tools::GetInstance()->SplitString(color, ret, ",", " ");

        assert(ret.size() == GeoColor::Size());
        
        double r = atof(ret[0].c_str());
        double g = atof(ret[1].c_str());
        double b = atof(ret[2].c_str());
        double a = atof(ret[3].c_str());

        m_openGL.m_light.m_color = GeoColor(r, g, b, a);
    }

    if (light["ambient"].isNull())
    {
        Log::GetInstance()->OutputConsole("light ambient information is missed");
        m_openGL.m_light.m_ambient = GeoVector3D(0.2f, 0.2f, 0.2f);
    }
    else
    {
        std::string ambient = light["ambient"].asString();
        std::vector<std::string> ret;

        Tools::GetInstance()->SplitString(ambient, ret, ",", " ");

        assert(ret.size() == GeoVector3D::Size());
        
        double x = atof(ret[0].c_str());
        double y = atof(ret[1].c_str());
        double z = atof(ret[2].c_str());

        m_openGL.m_light.m_ambient = GeoVector3D(x, y, z);
    }

    if (light["specular"].isNull())
    {
        Log::GetInstance()->OutputConsole("light specular information is missed");
        m_openGL.m_light.m_specular = GeoVector3D(1.0f, 1.0f, 1.0f);
    }
    else
    {
        std::string specular = light["specular"].asString();
        std::vector<std::string> ret;

        Tools::GetInstance()->SplitString(specular, ret, ",", " ");

        assert(ret.size() == GeoVector3D::Size());
        
        double x = atof(ret[0].c_str());
        double y = atof(ret[1].c_str());
        double z = atof(ret[2].c_str());

        m_openGL.m_light.m_specular = GeoVector3D(x, y, z);
    }

    if (light["diffuse"].isNull())
    {
        Log::GetInstance()->OutputConsole("light diffuse information is missed");
        m_openGL.m_light.m_diffuse = GeoVector3D(0.5f, 0.5f, 0.5f);
    }
    else
    {
        std::string diffuse = light["diffuse"].asString();
        std::vector<std::string> ret;

        Tools::GetInstance()->SplitString(diffuse, ret, ",", " ");

        assert(ret.size() == GeoVector3D::Size());
        
        double x = atof(ret[0].c_str());
        double y = atof(ret[1].c_str());
        double z = atof(ret[2].c_str());

        m_openGL.m_light.m_diffuse = GeoVector3D(x, y, z);
    }

    m_openGL.m_light.m_source = light["light source"].isNull() ? DIRECTION_LIGHT : (LightSource_e)(light["light source"].asInt());
    m_openGL.m_light.m_pointAttenuationRange = light["point light range"].isNull() ? 0 : light["point light range"].asUInt();
    m_openGL.m_light.m_cutOff = light["cutOff"].isNull() ? 12.5f : light["cutOff"].asDouble();
    m_openGL.m_light.m_outerCutOff = light["outerCutOff"].isNull() ? 17.5 : light["outerCutOff"].asDouble();

    if (light["point light attenuation"].isNull())
    {
        Log::GetInstance()->OutputConsole("point light attenuation's information is missed");
        assert(0);
        return;
    }

    Json::Value attenuationArray = light["point light attenuation"];

    unsigned int range;
    for (unsigned int i = 0; i < attenuationArray.size(); i++)
    {
        Json::Value attenuation = attenuationArray[i];

        PointLightAttenuation pla;

        range = attenuation["range"].asUInt();
        pla.m_constant = attenuation["constant"].asDouble();
        pla.m_linear = attenuation["linear"].asDouble();
        pla.m_quadratic = attenuation["quadratic"].asDouble();

        m_openGL.m_light.m_pointAttenuation[range] = pla;
    }
}

void GeoSetting::ParseWindow(const Json::Value &window)
{
    Json::Value width, height;

    m_window.m_width = window["width"].isNull() ? 640 : window["width"].asInt();
    m_window.m_height = window["height"].isNull() ? 640 : window["height"].asInt();
}