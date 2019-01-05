#include "opengl_helper.h"

SINGLETON_IMPLEMENT(GeoOpenGLHelper);

GeoOpenGLHelper::GeoOpenGLHelper()
    : m_bindingPoint(0)
{
}

GeoOpenGLHelper::~GeoOpenGLHelper()
{
}

unsigned int GeoOpenGLHelper::RequestBindingPoint()
{
    unsigned int bp = m_bindingPoint;
    m_bindingPoint++;

    return bp;
}