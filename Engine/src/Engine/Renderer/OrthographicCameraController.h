#pragma once

#include "Engine/Renderer/OrthographicCamera.h"
#include "Engine/Core/Timestep.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace Engine
{
  class OrthographicCameraController
  {
  public:
    OrthographicCameraController(float aspectRatio, bool rotation = false);
    void OnUpdate(Timestep dt);
    void OnEvent(Event& event);
    inline OrthographicCamera& GetCamera() { return m_Camera; }
    inline const OrthographicCamera& GetCamera() const { return m_Camera; }
    float GetZoomLevel() const { return m_Zoom; }
    void SetZoomLevel(float zoom) { m_Zoom = zoom; }
  private:
    bool OnMouseScrolled(MouseScrolledEvent& event);
    bool OnWindowResized(WindowResizeEvent& event);
    float m_AspectRatio;
    float m_Zoom = 1.0f;
    bool m_CanRotate;
    OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 1.0f };
    float m_CameraRotation = 0.0f;
    float m_CameraTranslationSpeed = 5.0f;
    float m_CameraRotationSpeed = 180.0f;
  };
}

