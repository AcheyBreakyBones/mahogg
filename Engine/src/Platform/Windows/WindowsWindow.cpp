#include "enpch.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
//#include <glad/glad.h>
#include "Platform/OpenGL/OpenGLContext.h"

namespace Engine
{
  //static bool s_GLFWInitialized = false;
  static uint8_t s_GLFWWindowCount = 0;

  static void GLFWErrorCallback(int error, const char* description)
  {
    EN_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
  }

  Scope<Window> Window::Create(const WindowProps& props)
  {
    return CreateScope<WindowsWindow>(props);
  }

  WindowsWindow::WindowsWindow(const WindowProps& props)
  {
    EN_PROFILE_FUNCTION();

    Init(props);
  }

  WindowsWindow::~WindowsWindow()
  {
    EN_PROFILE_FUNCTION();

    Shutdown();
  }

  void WindowsWindow::Init(const WindowProps& props)
  {
    EN_PROFILE_FUNCTION();

    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    EN_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
    if (!s_GLFWWindowCount)
    {
      EN_PROFILE_SCOPE("glfwInit()");
      //EN_CORE_INFO("Initializing GLFW");
      int success = glfwInit();
      EN_CORE_ASSERT(success, "Could not initialize GLFW!");
      glfwSetErrorCallback(GLFWErrorCallback);
      //s_GLFWInitialized = true;
    }
    // Set GL Version 
    // (This prevents an exception from being thrown on glGenerateVertexArrays)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    {
      EN_PROFILE_SCOPE("glfwCreateWindow");
      m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
      ++s_GLFWWindowCount;
    }
    //glfwMakeContextCurrent(m_Window);
    //int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //EN_CORE_ASSERT(status, "Failed to initialize Glad!");
    m_Context = GraphicsContext::Create(m_Window);
    m_Context->Init();
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    // Set GLFW Callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
      {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;
        WindowResizeEvent event(width, height);
        data.EventCallback(event);
      });
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
      {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
      });
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
      {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action)
        {
          case GLFW_PRESS:
          {
            // key = key that was pressed, 0 = repeat count
            KeyPressedEvent event(key, 0);
            data.EventCallback(event);
            break;
          }
          case GLFW_RELEASE:
          {
            KeyReleasedEvent event(key);
            data.EventCallback(event);
            break;
          }
          case GLFW_REPEAT:
          {
            KeyPressedEvent event(key, 1);
            data.EventCallback(event);
            break;
          }
        }
      });

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
      {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        KeyTypedEvent event(keycode);
        data.EventCallback(event);
      });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
      {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action)
        {
          case GLFW_PRESS:
          {
            MouseButtonPressedEvent event(button);
            data.EventCallback(event);
            break;
          }
          case GLFW_RELEASE:
          {
            MouseButtonReleasedEvent event(button);
            data.EventCallback(event);
            break;
          }
        }
      });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
      {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
      });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
      {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
      });
  }

  void WindowsWindow::Shutdown()
  {
    EN_PROFILE_FUNCTION();

    glfwDestroyWindow(m_Window);
    --s_GLFWWindowCount;
    if (s_GLFWWindowCount == 0)
    {
      //EN_CORE_INFO("Terminating GLFW");
      glfwTerminate();
    }
  }

  void WindowsWindow::OnUpdate()
  {
    EN_PROFILE_FUNCTION();

    glfwPollEvents();
    //glfwSwapBuffers(m_Window);
    m_Context->SwapBuffers();
  }

  void WindowsWindow::SetVSync(bool enabled)
  {
    EN_PROFILE_FUNCTION();

    if (enabled)
    {
      glfwSwapInterval(1);
    }
    else
    {
      glfwSwapInterval(0);
    }
    m_Data.VSync = enabled;
  }
  bool WindowsWindow::IsVSync() const
  {
    return m_Data.VSync;
  }
}
