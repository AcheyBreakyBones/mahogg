#pragma once

#include "Engine/Core/Layer.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace Engine
{
  class ENGINE_API ImGuiLayer : public Layer
  {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    //void OnUpdate();
    //void OnEvent(Event& event);
    virtual void OnImGuiRender() override;
    void Begin();
    void End();
  //private:
    /*
    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
    bool OnMouseMovedEvent(MouseMovedEvent& e);
    bool OnMouseScrolledEvent(MouseScrolledEvent& e);
    bool OnKeyPressedEvent(KeyPressedEvent& e);
    bool OnKeyReleasedEvent(KeyReleasedEvent& e);
    bool OnKeyTypedEvent(KeyTypedEvent& e);
    bool OnWindowResizeEvent(WindowResizeEvent& e);
    */
  //private:
  //  float m_Time = 0.0f;
  };
}

