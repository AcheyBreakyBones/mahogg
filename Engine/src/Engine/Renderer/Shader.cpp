#include "enpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine
{
  Shader* Shader::Create(const std::string& path)
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::NONE:   EN_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL: return new OpenGLShader(path);
    }

    EN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::NONE:    EN_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
    }
    EN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}