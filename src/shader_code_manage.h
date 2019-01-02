#if !defined(__SHADER_CODE_MANAGE_HEAD_FILE)
#define __SHADER_CODE_MANAGE_HEAD_FILE

#include "global_def.h"
#include "global_enum.h"
#include <string>
#include <map>

struct GeoShaderCode
{
    GeoShaderCode();

    std::string m_vertex;
    std::string m_fragment;
};

class GeoShaderCodeMgr final
{
  public:
    GeoShaderCodeMgr();
    ~GeoShaderCodeMgr();

  public:
    const GeoShaderCode &GetShaderCode(ShaderCodeType_e type) const;

  public:
    SINGLETON_DECLARE(GeoShaderCodeMgr);

  protected:
    void Init();

  private:
    std::map<ShaderCodeType_e, GeoShaderCode> m_codes;
};

#endif // __SHADER_CODE_MANAGE_HEAD_FILE
