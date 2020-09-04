#include "enpch.h"
#include "Renderer.h"

namespace Engine
{
  Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

  void Renderer::BeginScene(OrthographicCamera& camera) 
  {
    s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
  }

  void Renderer::EndScene() {}

  // After the shader is bound, call this function to
  // bind the vertex array THEN draw the shape
  void Renderer::Submit(const std::shared_ptr<Shader>& shader, 
                        const std::shared_ptr<VertexArray>& vertexArray, 
                        const glm::mat4& transform)
  {
    shader->Bind();
    shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
    shader->UploadUniformMat4("u_Transform", transform);
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }
}