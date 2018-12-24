#include "shader.h"
#include "log.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader()
    : m_programID(0)
{
}

Shader::~Shader()
{
    DeleteProgram();
}

bool Shader::Init(const std::string &vertexPath, const std::string &fragmentPath)
{
    DeleteProgram();

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        Log::GetInstance()->OutputConsole("open shader file failed", Level_Fatal);
        return false;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
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
    assert(m_programID != 0);

    glUseProgram(m_programID);
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

void Shader::SetFloat(const std::string &name, float value) const
{
    Use();
    glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
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
