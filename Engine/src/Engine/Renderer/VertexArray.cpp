#include "enpch.h"
#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
  Ref<VertexArray >VertexArray::Create()
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::NONE:   EN_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
    }

    EN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}