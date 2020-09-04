#include "enpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine
{
  VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::NONE:   EN_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
    }

    EN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::NONE:   EN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
    }

    EN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}