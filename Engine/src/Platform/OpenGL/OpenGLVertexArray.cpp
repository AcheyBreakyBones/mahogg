#include "enpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Engine
{
  static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
  {
    switch (type)
    {
    case ShaderDataType::Float:   return GL_FLOAT;
    case ShaderDataType::Float2:  return GL_FLOAT;
    case ShaderDataType::Float3:  return GL_FLOAT;
    case ShaderDataType::Float4:  return GL_FLOAT;
    case ShaderDataType::Mat3:    return GL_FLOAT;
    case ShaderDataType::Mat4:    return GL_FLOAT;
    case ShaderDataType::Int:     return GL_INT;
    case ShaderDataType::Int2:    return GL_INT;
    case ShaderDataType::Int3:    return GL_INT;
    case ShaderDataType::Int4:    return GL_INT;
    case ShaderDataType::Bool:    return GL_BOOL;
    }
    EN_CORE_ASSERT(false, "Unknown Shader DataType!");
    return 0;
  }

  Engine::OpenGLVertexArray::OpenGLVertexArray()
  {
    EN_PROFILE_FUNCTION();

    glCreateVertexArrays(1, &m_RendererID);
  }

  Engine::OpenGLVertexArray::~OpenGLVertexArray()
  {
    EN_PROFILE_FUNCTION();

    glDeleteVertexArrays(1, &m_RendererID);
  }

  void Engine::OpenGLVertexArray::Bind() const
  {
    EN_PROFILE_FUNCTION();

    glBindVertexArray(m_RendererID);
  }

  void Engine::OpenGLVertexArray::Unbind() const
  {
    EN_PROFILE_FUNCTION();

    glBindVertexArray(0);
  }

  void Engine::OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
  {
    EN_PROFILE_FUNCTION();

    // Check that the vertex buffer has a layout
    EN_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

    // Bind the vertex array
    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();

    // For each element in the layout, define its data
    const auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : layout)
    {
      glEnableVertexAttribArray(m_VBIndex);
      glVertexAttribPointer(m_VBIndex,
        element.GetComponentCount(),
        ShaderDataTypeToOpenGLBaseType(element._type),
        element._normalized ? GL_TRUE : GL_FALSE,
        layout.GetStride(),
        (const void*)(intptr_t)element._offset);
      ++m_VBIndex;
    }
    m_VertexBuffers.push_back(vertexBuffer);
  }

  void Engine::OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
  {
    EN_PROFILE_FUNCTION();

    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
  }
}
