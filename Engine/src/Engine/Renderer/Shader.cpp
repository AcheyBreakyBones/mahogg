#include "enpch.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine
{
  Ref<Shader> Shader::Create(const std::string& path)
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::NONE:   EN_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(path);
    }

    EN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::NONE:    EN_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
    }
    EN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
  {
    // Don't add a duplicate shader to the map!
    EN_CORE_ASSERT(!Exists(name), "Shader already exists!");
    m_Shaders[name] = shader;
  }

  void ShaderLibrary::Add(const Ref<Shader>& shader)
  {
    auto& name = shader->GetName();
    Add(name, shader);
  }

  Ref<Shader> ShaderLibrary::Load(const std::string& path)
  {
    Ref<Shader> shader = Shader::Create(path);
    Add(shader);
    return shader;
  }

  Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
  {
    Ref<Shader> shader = Shader::Create(path);
    Add(name, shader);
    return shader;
  }

  Ref<Shader> ShaderLibrary::Get(const std::string& name)
  {
    EN_CORE_ASSERT(Exists(name), "Shader does not exist!");
    return m_Shaders[name];
  }

  bool ShaderLibrary::Exists(const std::string& name) const
  {
    // If the shader is found before the end of the map is reached,
    // return true. Else, return false.
    return m_Shaders.find(name) != m_Shaders.end();
  }
}