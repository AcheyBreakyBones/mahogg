#include "enpch.h"
#include "Engine/Renderer/GraphicsContext.h"
#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Engine
{
  Scope<GraphicsContext> Engine::GraphicsContext::Create(void* window)
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::NONE:    EN_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
    }
    EN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}