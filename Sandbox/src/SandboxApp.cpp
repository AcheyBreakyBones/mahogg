#include <Engine.h>
#include "imgui/imgui.h"

class ExampleLayer : public Engine::Layer
{
public:
  ExampleLayer() : Layer("Example") {}

  void OnUpdate() override 
  { 
    //EN_INFO("ExampleLayer::Update");
    if (Engine::Input::IsKeyPressed((int)FunctionKeys::EN_KEY_TAB))
    {
      EN_TRACE("Tab key was pressed (poll)!");
    }
  }


  void OnEvent(Engine::Event& event) override 
  { 
  //  EN_TRACE("{0}", event);
    if (event.GetEventType() == Engine::EventType::KeyPressed)
    {
      Engine::KeyPressedEvent& e = (Engine::KeyPressedEvent&)event;
      if (e.GetKeyCode() == (int)FunctionKeys::EN_KEY_TAB)
      {
        EN_TRACE("Tab key was pressed (event)!");
      }
      EN_TRACE("{0}", (char)e.GetKeyCode());
    }
  }

  virtual void OnImGuiRender() override
  {
    ImGui::Begin("Test");
    ImGui::Text("Hello World");
    ImGui::End();
  }
};

class Sandbox : public Engine::Application
{
public:
  Sandbox() 
  { 
    PushLayer(new ExampleLayer());
    //PushOverlay(new Engine::ImGuiLayer());
  }

  ~Sandbox() {}
};

Engine::Application* Engine::CreateApplication()
{
  return new Sandbox();
}