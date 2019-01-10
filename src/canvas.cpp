#include "canvas.h"
#include <assert.h>
#include "log.h"
#include <vector>
#include "shader_code_manage.h"

GeoCanvas::GeoCanvas(const unsigned int width, const unsigned int height)
    : m_fbo(0), m_multiText(0), m_rbo(0), m_vao(0), m_vbo(0), m_inerFBO(0), m_screenTexture(0), m_height(0), m_width(0)
{
    Init(width, height);
}

GeoCanvas::~GeoCanvas()
{
    Clear();
}

void GeoCanvas::Active()
{
    assert(m_fbo > 0);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GeoCanvas::Deactive()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_inerFBO);
    glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glDisable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_shader.Use();
    glBindVertexArray(m_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_screenTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GeoCanvas::Init(const unsigned int width, const unsigned int height)
{
    Clear();

    m_height = height;
    m_width = width;

    SetupVertices();
    SetupFrameBuffer(width, height);
    SetupShader();
}

void GeoCanvas::Clear()
{
    if (m_fbo > 0)
    {
        glDeleteFramebuffers(1, &m_fbo);
    }

    if (m_inerFBO)
    {
        glDeleteFramebuffers(1, &m_inerFBO);
    }

    if (m_multiText > 0)
    {
        glDeleteTextures(1, &m_multiText);
    }

    if (m_screenTexture > 0)
    {
        glDeleteTextures(1, &m_screenTexture);
    }

    if (m_rbo > 0)
    {
        glDeleteRenderbuffers(1, &m_rbo);
    }

    if (m_vao > 0)
    {
        glDeleteVertexArrays(1, &m_vao);
    }

    if (m_vbo > 0)
    {
        glDeleteBuffers(1, &m_vbo);
    }
}

void GeoCanvas::SetupVertices()
{
    float vertices[] = {
        // positions   // texCoords
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f};

    glGenVertexArrays(1, &m_vao);
    assert(m_vao > 0);

    glGenBuffers(1, &m_vbo);
    assert(m_vbo > 0);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
}

void GeoCanvas::SetupFrameBuffer(const unsigned int width, const unsigned int height)
{
    // framebuffer configuration
    glGenFramebuffers(1, &m_fbo);
    assert(m_fbo > 0);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // create a color attachment texture
    glGenTextures(1, &m_multiText);
    assert(m_multiText > 0);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_multiText);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, width, height, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_multiText, 0);

    // create a renderbuffer object for depth and stencil attachment
    glGenRenderbuffers(1, &m_rbo);
    assert(m_rbo > 0);
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        Log::GetInstance()->OutputConsole("ERROR::FRAMEBUFFER:: Framebuffer is not complete!", Level_Fatal);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // configure second post-processing framebuffer
    glGenFramebuffers(1, &m_inerFBO);
    assert(m_inerFBO > 0);
    glBindFramebuffer(GL_FRAMEBUFFER, m_inerFBO);

    // create a color attachment texture
    glGenTextures(1, &m_screenTexture);
    assert(m_screenTexture > 0);
    glBindTexture(GL_TEXTURE_2D, m_screenTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_screenTexture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        Log::GetInstance()->OutputConsole("ERROR::FRAMEBUFFER:: Intermediate Framebuffer is not complete!", Level_Fatal);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GeoCanvas::SetupShader()
{
    const GeoShaderCode &shaderCodes = GeoShaderCodeMgr::GetInstance()->GetShaderCode(SCT_Screen);

    m_shader.SetShaderCodes(shaderCodes.m_vertex, shaderCodes.m_fragment);
    m_shader.Complie();

    m_shader.SetInt("screenTexture", 0);
}