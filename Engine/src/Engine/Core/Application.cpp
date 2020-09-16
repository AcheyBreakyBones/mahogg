#include "enpch.h"
#include "Application.h"
//#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Core/Log.h"
#include <GLFW/glfw3.h>
#include "Engine/Renderer/Renderer.h"
#include "Input.h"

namespace Engine
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
  Application* Application::s_Instance = nullptr;

  // TODO: Defaut ctor for OrthographicCamera???
  Application::Application()
  {
    // Create Window
    EN_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;
    m_Window = Engine::Scope<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    Renderer::Init();
    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
  }

  Application::~Application()
  {
  }

  void Application::Run()
  {
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
      float time = (float)glfwGetTime();
      Timestep dt = time - m_LastFrameTime;
      m_LastFrameTime = time;

      // Submit layers for rendering if window is visible
      if (!m_Minimized)
      {
        for (Layer* layer : m_LayerStack)
        {
          layer->OnUpdate(dt);
        }
      }

      // Commence rendering
      m_ImGuiLayer->Begin();
      for (Layer* layer : m_LayerStack)
      {
        layer->OnImGuiRender();
      }
      m_ImGuiLayer->End();

      m_Window->OnUpdate();
    }
  }

  void Application::PushLayer(Layer* layer)
  {
    m_LayerStack.PushLayer(layer);
  }

  void Application::PushOverlay(Layer* layer)
  {
    m_LayerStack.PushOverlay(layer);
  }

  void Application::OnEvent(Event& event)
  {
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
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