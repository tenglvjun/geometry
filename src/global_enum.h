#if !defined(__GLOBAL_ENUM_HEAD_FILE__)
#define __GLOBAL_ENUM_HEAD_FILE__

typedef enum
{
  DIRECTION_LIGHT = 0,
  POINT_LIGHT,
  SPOT_LIGTH
} LightSource_e;

typedef enum
{
  Level_Info = 0,
  Level_Warning,
  Level_Error,
  Level_Fatal,
} LogLevel_e;

typedef enum
{
  PT_Invalid = 0,
  PT_Persp,
  PT_Persp_Infinite,
  PT_Ortho
} ProjType_e;

typedef enum
{
  SCT_Invalid = 0,
  SCT_Light,
  SCT_Camera,
  SCT_Mesh,
  SCT_Screen,
  SCT_Count,
} ShaderCodeType_e;

#endif // __GLOBAL_ENUM_HEAD_FILE__
