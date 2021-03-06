#include "enpch.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Log.h"
#include <GLFW/glfw3.h>
#include "Engine/Renderer/Renderer.h"
#include "Engine/Core/Input.h"

namespace Engine
{
  Application* Application::s_Instance = nullptr;

  // TODO: Defaut ctor for OrthographicCamera???
  Application::Application()
  {
    EN_PROFILE_FUNCTION();

    // Create Window
    EN_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;
    m_Window = Window::Create();
    m_Window->SetEventCallback(EN_BIND_EVENT_FN(Application::OnEvent));
    Renderer::Init();
    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
  }

  Application::~Application()
  {
    EN_PROFILE_FUNCTION();

    Renderer::Shutdown();
  }

  void Application::Run()
  {
    EN_PROFILE_FUNCTION();

    /*
    WindowResizeEvent e(1920, 1080);
    if (e.IsInCategory(EventCategoryApplication))
    {
      EN_TRACE(e);
    }
    if (e.IsInCategory(EventCategoryInput))
    {
      EN_TRACE(e);
    }

    while (true);
    */
    while (m_Running)
    {
      EN_PROFILE_SCOPE("RunLoop");
      float time = (float)glfwGetTime();
      Timestep dt = time - m_LastFrameTime;
      m_LastFrameTime = time;

      // Submit layers for rendering if window is visible
      if (!m_Minimized)
      {
        EN_PROFILE_SCOPE("LayerStack OnUpdate");
        for (Layer* layer : m_LayerStack)
        {
          layer->OnUpdate(dt);
        }
      }

      // Commence rendering
      m_ImGuiLayer->Begin();
      for (Layer* layer : m_LayerStack)
      {
        EN_PROFILE_SCOPE("LayerStack OnImGuiRender");
        for (Layer* layer : m_LayerStack)
        {
          layer->OnImGuiRender();
        }
      }
      m_ImGuiLayer->End();

      m_Window->OnUpdate();
    }
  }

  void Application::PushLayer(Layer* layer)
  {
    EN_PROFILE_FUNCTION();

    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  void Application::PushOverlay(Layer* layer)
  {
    EN_PROFILE_FUNCTION();

    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
  }

  void Application::OnEvent(Event& event)
  {
    EN_PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(EN_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(EN_BIND_EVENT_FN(Application::OnWindowResize));
    //EN_CORE_TRACE("{0}", e);
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
    {
      (*--it)->OnEvent(event);
      if (event.Handled)
      {
        break;
      }
    }
  }

  bool Application::OnWindowClose(WindowCloseEvent& e)
  {
    m_Running = false;
    return true;
  }
  bool Application::OnWindowResize(WindowResizeEvent& event)
  {
    EN_PROFILE_FUNCTION();

    if (event.GetWidth() == 0 || event.GetHeight() == 0)
    {
      m_Minimized = true;
      return false;
    }
    m_Minimized = false;
    Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
    return false;
  }
}