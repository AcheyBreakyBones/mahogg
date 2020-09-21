#include "enpch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
//#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
  struct Renderer2DStorage
  {
    Ref<VertexArray> QuadVertexArray;
    Ref<Shader> FlatColorShader;
    Ref<Shader> TextureShader;
  };

  // RAW POINTER???
  static Scope<Renderer2DStorage> s_Data;
  //static Renderer2DStorage* s_Data;

  void Renderer2D::Init()
  {
    s_Data = CreateScope<Renderer2DStorage>();
    //s_Data = new Renderer2DStorage();
    s_Data->QuadVertexArray = VertexArray::Create();

    float squareVertices[5 * 4] = 
    {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
       0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
       0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
      -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    // Store vertices in vertex buffer
    Ref<VertexBuffer> squareVB;
    squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

    // Layout
    // First three floats of VB are x, y, and z
    BufferLayout layout = {
      { ShaderDataType::Float3, "a_Position" },
      { ShaderDataType::Float2, "a_TexCoord" }
    };

    // Set VB's layer and then add it to the VA
    squareVB->SetLayout(layout);
    s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

    // Index Buffer (aka: the order in which vertices are drawn)
    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Ref<IndexBuffer> squareIB;
    squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) /
      sizeof(uint32_t)));
    s_Data->QuadVertexArray->SetIndexBuffer(squareIB);
    s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
    s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetInt("u_Texture", 0);
  }

  void Renderer2D::Shutdown()
  {
    //delete s_Data;
  }

  void Renderer2D::BeginScene(const OrthographicCamera& camera)
  {
    //std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
    //std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->
    //  UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    //std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->
    //  UploadUniformMat4("u_Transform", glm::mat4(1.0f));
    s_Data->FlatColorShader->Bind();
    s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
  }

  void Renderer2D::EndScene()
  {
  }

  void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
  {
    DrawQuad({ position.x, position.y, 0.0f }, size, color);
  }

  void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
  {
    //std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
    //std::dynamic_pointer_cast<Engine::OpenGLShader>(s_Data->FlatColorShader)->UploadUniformFloat4("u_Color", color);
    s_Data->FlatColorShader->Bind();
    s_Data->FlatColorShader->SetFloat4("u_Color", color);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    s_Data->FlatColorShader->SetMat4("u_Transform", transform);

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
  }

  void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
  {
    DrawQuad({ position.x, position.y, 0.0f }, size, texture);
  }

  void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
  {
    s_Data->TextureShader->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    s_Data->TextureShader->SetMat4("u_Transform", transform);

    texture->Bind();

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
  }
}