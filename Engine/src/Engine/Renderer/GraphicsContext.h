#pragma once

// Base class for OpenGLContext

namespace Engine
{
  class GraphicsContext
  {
  public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
  };
}