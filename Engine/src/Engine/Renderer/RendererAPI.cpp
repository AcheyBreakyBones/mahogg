#include "enpch.h"
#include "Engine/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Engine
{
  RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

  Scope<RendererAPI> RendererAPI::Create()
  {
    switch (s_API)
    {
    case RendererAPI::API::NONE:    EN_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
    }
    EN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}