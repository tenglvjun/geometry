#if !defined(__SHADER_HEAD_FILE__)
#define __SHADER_HEAD_FILE__

#include <glad/glad.h>
#include <string>

class Shader final
{
public:
  Shader();
  ~Shader();

public:
  void SetShaderCodes(const std::string &vertexCodes, const std::string &fragmentCodes);
  bool Complie();
  void Use() const;
  bool IsUsing() const;
  unsigned int GetID() const;
  unsigned int GetUniformBlockIndex(const std::string &name) const;
  unsigned int GetUniformBlockSize(const std::string &name) const;
  void BindUniformBlock(const std::string &name, const unsigned int bindingPoint) const;
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
  unsigned int m_programID;
  std::string m_vertexCodes;
  std::string m_fragmentCodes;
};

#endif // __SHADER_HEAD_FILE__
