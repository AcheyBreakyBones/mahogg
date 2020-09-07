#include "enpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Engine
{
  Ref<Texture2D> Texture2D::Create(const std::string& path)
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::NONE:    EN_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
    }
    EN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}