#include "shader_code_manage.h"
#include "tools.h"
#include <assert.h>

GeoShaderCode::GeoShaderCode()
{
}

SINGLETON_IMPLEMENT(GeoShaderCodeMgr);

GeoShaderCodeMgr::GeoShaderCodeMgr()
{
    Init();
}

GeoShaderCodeMgr::~GeoShaderCodeMgr()
{
}

const GeoShaderCode &GeoShaderCodeMgr::GetShaderCode(ShaderCodeType_e type) const
{
    std::map<ShaderCodeType_e, GeoShaderCode>::const_iterator iter = m_codes.find(type);

    assert(iter != m_codes.end());

    return iter->second;
}

void GeoShaderCodeMgr::Init()
{
    std::string vertex, fragment;

    for (unsigned int i = SCT_Invalid + 1; i < SCT_Count; i++)
    {
        vertex = "shader/";
        fragment = "shader/";

        switch (i)
        {
        case SCT_Light:
        {
            vertex += "light";
            fragment += "light";
        }
        break;
        case SCT_Camera:
        {
            vertex += "camera";
            fragment += "camera";
        }
        break;
        case SCT_Mesh:
        {
            vertex += "mesh";
            fragment += "mesh";
        }
        break;
        case SCT_Screen:
        {
            vertex += "screen";
            fragment += "screen";
        }
        break;
        default:
            break;
        }

        vertex += ".vs";
        fragment += ".fs";

        GeoShaderCode code;
        code.m_vertex = Tools::ReadFile(vertex);
        code.m_fragment = Tools::ReadFile(fragment);

        m_codes[(ShaderCodeType_e)i] = code;
    }
}