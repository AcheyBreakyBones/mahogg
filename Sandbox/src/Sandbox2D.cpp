#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
  : Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f)
{
}

void Sandbox2D::OnAttach()
{
  m_KirbyTexture = Engine::Texture2D::Create("assets/textures/Kirby.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Engine::Timestep dt)
{
  // LIGHTS! (clear screen)
  Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
  Engine::RenderCommand::Clear();

  // CAMERA! (set camera)
  m_CameraController.OnUpdate(dt);

  // ACTION! (begin scene)
  Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
    // drawing quads
  //Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
  Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
  Engine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
  Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_KirbyTexture);

  // CUT! (end scene)
  Engine::Renderer::EndScene();
  // TODO: Add functions Shader::SetMat4, Shader::SetFloat4
  // std::synamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->
  //   Bind();
  // std::synamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->
  //   UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2D::OnImGuiRender()
{
  ImGui::Begin("Settings");
  ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
  ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& event)
{
  m_CameraController.OnEvent(event);
}
