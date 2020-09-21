#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Engine
{
  class Renderer2D
  {
  public:
    static void Init();
    static void Shutdown();
    static void BeginScene(const OrthographicCamera& camera);
    static void EndScene();

    // Primitives
      // vec2 position
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    // vec3 position
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

    // Textures
      // vec2 position
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
    // vec3 position
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
  };
}