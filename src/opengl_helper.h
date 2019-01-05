#if !defined(__OPENGL_HELPER_HEAD_FILE__)
#define __OPENGL_HELPER_HEAD_FILE__

#include "global_def.h"

class GeoOpenGLHelper final
{
  public:
    GeoOpenGLHelper();
    ~GeoOpenGLHelper();

  public:
    unsigned int RequestBindingPoint();

  public:
    SINGLETON_DECLARE(GeoOpenGLHelper);

  private:
    GeoOpenGLHelper(const GeoOpenGLHelper &helper);
    GeoOpenGLHelper &operator=(const GeoOpenGLHelper &helper);

  private:
    unsigned int m_bindingPoint;
};

#endif // __OPENGL_HELPER_HEAD_FILE__
