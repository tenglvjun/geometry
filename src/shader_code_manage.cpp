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
        vertex = "shader/vertex/";
        fragment = "shader/fragment/";

        switch (i)
        {
        case SCT_Light:
        {
            vertex = "";
            fragment += "light.fs";
        }
        break;
        case SCT_Camera:
        {
            vertex += "camera.vs";
            fragment = "";
        }
        break;
        case SCT_Mesh:
        {
            vertex += "mesh.vs";
            fragment += "mesh.fs";
        }
        break;
        default:
            break;
        }

        GeoShaderCode code;

        if (!vertex.empty())
        {
            code.m_vertex = Tools::GetInstance()->ReadFile(vertex);
        }

        if (!fragment.empty())
        {
            code.m_fragment = Tools::GetInstance()->ReadFile(fragment);
        }

        m_codes[(ShaderCodeType_e)i] = code;
    }
}