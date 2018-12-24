#if !defined(__SHADER_HEAD_FILE__)
#define __SHADER_HEAD_FILE__

#include <glad/glad.h>
#include <string>
#include <assert.h>

class Shader final
{
public:
  Shader();
  virtual ~Shader();

public:
  bool Init(const std::string &vertexPath, const std::string &fragmentPath);
  void Use() const;
  GLuint GetID() const;
  void SetBool(const std::string &name, bool value) const;
  void SetInt(const std::string &name, int value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetMatrix(const std::string &name, bool transpose, float *values) const;

protected:
  void DeleteProgram();
  void CheckCompileErrors(unsigned int shader, std::string type);

protected:
  GLuint m_programID;
};

#endif // __SHADER_HEAD_FILE__
