#include "enpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine
{
  Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

  void Renderer::Init()
  {
    RenderCommand::Init();
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
  void Renderer::Submit(const Engine::Ref<Shader>& shader, 
                        const Engine::Ref<VertexArray>& vertexArray, 
                        const glm::mat4& transform)
  {
    shader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }
}