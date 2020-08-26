#include "enpch.h"
#include "Application.h"
//#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"
//#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Input.h"

namespace Engine
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
  Application* Application::s_Instance = nullptr;

  Application::Application()
  {
    // Create Window
    EN_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    // Vertex Array
    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    // Vertex Buffer
    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    float vertices[3 * 3] =
    {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
    };

      // Upload data to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    // Index Buffer
    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

    unsigned int indices[3] = { 0, 1, 2 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

    std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position + 0.5, 1.0);
			}
		)";

    m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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
      glClearColor(0.1f, 0.1f, 0.1f, 1);
      glClear(GL_COLOR_BUFFER_BIT);

      m_Shader->Bind();
      glBindVertexArray(m_VertexArray);
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

      // Submit layers for rendering
      for (Layer* layer : m_LayerStack)
      {
        layer->OnUpdate();
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
    layer->OnAttach();
  }

  void Application::PushOverlay(Layer* layer)
  {
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
  }

  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
    //EN_CORE_TRACE("{0}", e);
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
    {
      (*--it)->OnEvent(e);
      if (e.Handled)
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
}