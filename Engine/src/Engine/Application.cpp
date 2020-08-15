#include "Application.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"

namespace Engine
{
  Application::Application()
  {
  }

  Application::~Application()
  {
  }

  void Application::Run()
  {
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
  }
}