#include "enpch.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Renderer2D.h"

namespace Engine
{
  Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

  void Renderer::Init()
  {
    RenderCommand::Init();
    Renderer2D::Init();
  }

  void Renderer::OnWindowResize(uint32_t width, uint32_t height)
  {
    RenderCommand::SetViewport(0, 0, width, height);
  }

  void Renderer::BeginScene(OrthographicCamera& camera) 
  {
    s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
  }

  void Renderer::EndScene() {}

  // After the shader is bound, call this function to
  // bind the vertex array THEN draw the shape
  void Renderer::Submit(const Ref<Shader>& shader, 
                        const Ref<VertexArray>& vertexArray, 
                        const glm::mat4& transform)
  {
    shader->Bind();
    shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
    shader->SetMat4("u_Transform", transform);
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }

  void Renderer::Shutdown()
  {
    Renderer2D::Shutdown();
  }
}