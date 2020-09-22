#pragma once

#include "Engine/Renderer/OrthographicCamera.h"
#include "Engine/Renderer/Texture.h"

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
    static void DrawQuadColor2(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    // vec3 position
    static void DrawQuadColor3(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

    // Textures
      // vec2 position
    static void DrawQuadTex2(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
    // vec3 position
    static void DrawQuadTex3(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
  };
}