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
  PT_None = 0,
  PT_Persp,
  PT_Persp_Infinite,
  PT_Ortho
} ProjType_e;

#endif // __GLOBAL_ENUM_HEAD_FILE__
