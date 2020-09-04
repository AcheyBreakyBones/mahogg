#include "enpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
  VertexArray* VertexArray::Create()
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::NONE:   EN_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
    }

    EN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}