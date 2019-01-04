#include "shader.h"
#include "log.h"
#include <iostream>
#include <assert.h>
#include "setting.h"

Shader::Shader()
    : m_programID(0)
{
}

Shader::~Shader()
{
    DeleteProgram();
}

void Shader::SetShaderCodes(const std::vector<std::string> &vertexCodes, const std::vector<std::string> &fragmentCodes)
{
    OpenGLConfig &config = GeoSetting::GetInstance()->OpenGLConfig();

    std::string version = config.m_shaderVersion + "\n";
    m_vertexCodes = version;
    for (size_t i = 0; i < vertexCodes.size(); i++)
    {
        m_vertexCodes += vertexCodes[i];
    }

    m_fragmentCodes = version;
    for (size_t i = 0; i < fragmentCodes.size(); i++)
    {
        m_fragmentCodes += fragmentCodes[i];
    }
}

bool Shader::Complie()
{
    DeleteProgram();

    GLuint vertex, fragment;

    GLint vSourceLength = (GLint)m_vertexCodes.length();
    GLint fSourceLength = (GLint)m_fragmentCodes.length();

    const char *buf = nullptr;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    buf = m_vertexCodes.c_str();
    glShaderSource(vertex, 1, &buf, &vSourceLength);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    buf = m_fragmentCodes.c_str();
    glShaderSource(fragment, 1, &buf, &fSourceLength);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertex);
    glAttachShader(m_programID, fragment);
    glLinkProgram(m_programID);
    CheckCompileErrors(m_programID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

void Shader::Use() const
{
    if (!IsUsing())
    {
        glUseProgram(m_programID);
    }
}

bool Shader::IsUsing() const
{
    assert(m_programID != 0);

    GLint programID;
    glGetIntegerv(GL_CURRENT_PROGRAM, &programID);

    return (programID == m_programID);
}

GLuint Shader::GetID() const
{
    return m_programID;
}

void Shader::SetBool(const std::string &name, bool value) const
{
    Use();
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const
{
    Use();
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::SetUInt(const std::string &name, unsigned int value) const
{
    Use();
    glUniform1ui(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const
{
    Use();
    glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::SetVector(const std::string &name, unsigned int dim, float *values) const
{
    assert((dim >= 2) && (dim <= 4));

    Use();

    switch (dim)
    {
    case 2:
    {
        glUniform2fv(glGetUniformLocation(m_programID, name.c_str()), 1, values);
        break;
    }

    case 3:
    {
        glUniform3fv(glGetUniformLocation(m_programID, name.c_str()), 1, values);
        break;
    }

    case 4:
    {
        glUniform4fv(glGetUniformLocation(m_programID, name.c_str()), 1, values);
        break;
    }

    default:
        break;
    }
}

void Shader::SetMatrix(const std::string &name, bool transpose, float *values) const
{
    Use();
    glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, transpose ? GL_TRUE : GL_FALSE, values);
}

void Shader::DeleteProgram()
{
    if (m_programID != 0)
    {
        glDeleteProgram(m_programID);
    }
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    std::string msg;
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);

            msg = "ERROR::SHADER_COMPILATION_ERROR of type: ";
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);

            msg = "ERROR::PROGRAM_LINKING_ERROR of type: ";
        }
    }

    if (!msg.empty())
    {
        msg += type + ", info: " + infoLog;

        Log::GetInstance()->OutputConsole(msg, Level_Error);
    }
}
