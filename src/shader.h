#if !defined(__SHADER_HEAD_FILE__)
#define __SHADER_HEAD_FILE__

#include <glad/glad.h>
#include <string>
#include <vector>

class Shader final
{
public:
  Shader();
  ~Shader();

public:
  void SetShaderCodes(const std::vector<std::string> &vertexCodes, const std::vector<std::string> &fragmentCodes);
  bool Complie();
  void Use() const;
  bool IsUsing() const;
  GLuint GetID() const;
  void SetBool(const std::string &name, bool value) const;
  void SetInt(const std::string &name, int value) const;
  void SetUInt(const std::string &name, unsigned int value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetVector(const std::string &name, unsigned int dim, float *values) const;
  void SetMatrix(const std::string &name, bool transpose, float *values) const;

protected:
  void DeleteProgram();
  void CheckCompileErrors(unsigned int shader, std::string type);

public:
protected:
  GLuint m_programID;
  std::string m_vertexCodes;
  std::string m_fragmentCodes;
};

#endif // __SHADER_HEAD_FILE__
