#pragma once

#include "Engine/Renderer/Shader.h"
#include <glm/glm.hpp>

// Temporary
typedef unsigned int GLenum;

namespace Engine
{
  class OpenGLShader : public Shader
  {
  public:
    OpenGLShader(const std::string& path);
    OpenGLShader(const std::string& name, const std::string& vertexSrc, 
                 const std::string& fragmentSrc);
    virtual ~OpenGLShader();
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual void SetInt(const std::string& name, int val) override;
    virtual void SetFloat3(const std::string& name, const glm::vec3& val) override;
    virtual void SetFloat4(const std::string& name, const glm::vec4& val) override;
    virtual void SetMat4(const std::string& name, const glm::mat4& val) override;
    inline virtual const std::string& GetName() const override 
    { 
      return m_Name; 
    }
    void UploadUniformInt(const std::string& name, int value);
    void UploadUniformFloat(const std::string& name, float value);
    void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
    void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
    void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
    void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
    void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
  private:
    std::string ReadFile(const std::string& path);
    std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
    void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
    uint32_t m_RendererID;  // Used for binding and deleting the shader
    std::string m_Name; 
  };
}

