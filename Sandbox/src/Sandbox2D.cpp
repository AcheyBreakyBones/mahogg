#include "Sandbox2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
  : Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f)
{
}

void Sandbox2D::OnAttach()
{
  EN_PROFILE_FUNCTION();

  m_CheckerboardTexture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
  EN_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Engine::Timestep dt)
{
  EN_PROFILE_FUNCTION();
  // LIGHTS! (clear screen)
  {
    EN_PROFILE_SCOPE("Clear Screen");
    Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Engine::RenderCommand::Clear();
  }

  // CAMERA! (set camera)
  m_CameraController.OnUpdate(dt);
  //{
  //  EN_PROFILE_SCOPE("Set Camera");
  //  m_CameraController.OnUpdate(dt);
  //}

  // ACTION! (begin scene)
  {
    EN_PROFILE_SCOPE("Begin Scene");
    Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
      // drawing quads
    //Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Engine::Renderer2D::DrawQuadColor2({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Engine::Renderer2D::DrawQuadColor2({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Engine::Renderer2D::DrawQuadTex3({ 0.0f, 0.0f, 0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
    // CUT! (end scene)
    Engine::Renderer::EndScene();
  }
}

void Sandbox2D::OnImGuiRender()
{
  EN_PROFILE_FUNCTION();

  ImGui::Begin("Settings");
  ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
  //for (auto& result : m_ProfileResults)
  //{
  //  char label[50];
  //  strcpy(label, "%.3fms ");
  //  strcat(label, result._name);
  //  EN_CORE_ASSERT(strlen(label) <= 50, "Label is greater than 50 characters!");
  //  ImGui::Text(label, result._time);
  //}
  //m_ProfileResults.clear();
  ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& event)
{
  m_CameraController.OnEvent(event);
}
