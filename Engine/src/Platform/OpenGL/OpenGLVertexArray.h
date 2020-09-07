#pragma once
#include "Engine/Renderer/VertexArray.h"

namespace Engine
{
  class OpenGLVertexArray : public VertexArray
  {
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual const std::vector<Engine::Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
    virtual void AddVertexBuffer(const Engine::Ref<VertexBuffer>& vertexBuffer) override;

    virtual const Engine::Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
    virtual void SetIndexBuffer(const Engine::Ref<IndexBuffer>& indexBuffer) override;
  private:
    uint32_t m_RendererID;
    uint32_t m_VBIndex = 0;
    std::vector<Engine::Ref<VertexBuffer>> m_VertexBuffers;
    Engine::Ref<IndexBuffer> m_IndexBuffer;
  };
}

