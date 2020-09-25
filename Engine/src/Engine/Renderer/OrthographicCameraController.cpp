#include "enpch.h"
#include "Engine/Renderer/OrthographicCameraController.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"

namespace Engine
{
  OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    : m_AspectRatio(aspectRatio), 
      m_Camera(-m_AspectRatio * m_Zoom, 
      m_AspectRatio * m_Zoom, 
     -m_Zoom, m_Zoom), 
      m_CanRotate(rotation) 
  {
  }

  void OrthographicCameraController::OnUpdate(Timestep dt)
  {
    EN_PROFILE_FUNCTION();

    if (Input::IsKeyPressed((int)PrintableKeys::EN_KEY_A))
    {
      m_CameraPosition.x -= m_CameraTranslationSpeed * dt;
    }
    else if (Input::IsKeyPressed((int)PrintableKeys::EN_KEY_D))
    {
      m_CameraPosition.x += m_CameraTranslationSpeed * dt;
    }

    if (Input::IsKeyPressed((int)PrintableKeys::EN_KEY_W))
    {
      m_CameraPosition.y += m_CameraTranslationSpeed * dt;
    }
    else if (Input::IsKeyPressed((int)PrintableKeys::EN_KEY_S))
    {
      m_CameraPosition.y -= m_CameraTranslationSpeed * dt;
    }

    if (m_CanRotate)
    {
      if (Input::IsKeyPressed((int)PrintableKeys::EN_KEY_Q))
      {
        m_CameraRotation += m_CameraRotationSpeed * dt;
      }
      if (Input::IsKeyPressed((int)PrintableKeys::EN_KEY_E))
      {
        m_CameraRotation -= m_CameraRotationSpeed * dt;
      }
      m_Camera.SetRotation(m_CameraRotation);
    }
    m_Camera.SetPosition(m_CameraPosition);
    m_CameraTranslationSpeed = m_Zoom;
  }

  // Scrolling the mouse wheel will resize the window
  void OrthographicCameraController::OnEvent(Event& event)
  {
    EN_PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseScrolledEvent>(EN_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(EN_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
  }

  bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
  {
    EN_PROFILE_FUNCTION();

    m_Zoom -= event.GetYOffset() * 0.25f;
    m_Zoom = std::max(m_Zoom, 0.25f);
    m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
    return false;
  }

  bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
  {
    EN_PROFILE_FUNCTION();

    m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
    m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
    return false;
  }
}