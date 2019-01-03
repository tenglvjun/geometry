#if !defined(__CANVAS_HEAD_FILE__)
#define __CANVAS_HEAD_FILE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

class GeoCanvas
{
public:
    GeoCanvas(const unsigned int width, const unsigned int height);
    virtual ~GeoCanvas();

public:
    void Active();
    void Deactive();

protected:
    void Init(const unsigned int width, const unsigned int height);
    void Clear();

    void SetupVertices();
    void SetupFrameBuffer(const unsigned int width, const unsigned int height);
    void SetupShader();

private:
    GeoCanvas(const GeoCanvas& canvas);
    GeoCanvas& operator=(const GeoCanvas& canvas);

protected:
    unsigned int m_fbo;
    unsigned int m_tcb;
    unsigned int m_rbo;
    unsigned int m_vao;
    unsigned int m_vbo;
    Shader m_shader;
};

#endif // __CANVAS_HEAD_FILE__
