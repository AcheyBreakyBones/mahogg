#include <Engine.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// This is where the Vertex Arrays and Shaders are defined
class ExampleLayer : public Engine::Layer
{
public:
  ExampleLayer()
    : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
  {
    // Vertex Array
    m_TriangleVA.reset(Engine::VertexArray::Create());

    // Vertex Buffer (x, y, z, R, G, B, A)
    float vertices[3 * 7] =
    {
      -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
       0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
       0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };

    // Store vertices in vertex buffer
    Engine::Ref<Engine::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

    // Layout and Index Buffer contained in this scope
    // (don't need them anymore once they get stored in vertex array)
    {
      // Layout
      // First three floats of VB are x, y, and z
      // Second four floats are R, G, B, and A
      Engine::BufferLayout layout = {
        { Engine::ShaderDataType::Float3, "a_Position" },
        { Engine::ShaderDataType::Float4, "a_Color" }
      };

      // Set VB's layer and then add it to the VA
      vertexBuffer->SetLayout(layout);
      m_TriangleVA->AddVertexBuffer(vertexBuffer);

      // Index Buffer (aka: the order in which vertices are drawn)
      uint32_t indices[3] = { 0, 1, 2 };
      Engine::Ref<Engine::IndexBuffer> indexBuffer;
      indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
      m_TriangleVA->SetIndexBuffer(indexBuffer);

      // Now this VA is complete
      m_SquareVA.reset(Engine::VertexArray::Create());

      // Vertex Buffer (x, y, z, U, V)
      // U and V are Texture Coordinates
      float squareVertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
      };

      // Set layout and add VB to VA
      Engine::Ref<Engine::VertexBuffer> squareVB;
      squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
      squareVB->SetLayout({
        { Engine::ShaderDataType::Float3, "a_Position" },
        { Engine::ShaderDataType::Float2, "a_TexCoord" }
        });
      m_SquareVA->AddVertexBuffer(squareVB);

      // Index Buffer
      uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
      Engine::Ref<Engine::IndexBuffer> squareIB;
      squareIB.reset(Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
      m_SquareVA->SetIndexBuffer(squareIB);
    }

    // Shaders

    // Triangle
    std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
      layout(location = 1) in vec4 a_Color;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;

			out vec3 v_Position;
      out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
        v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

    std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
      in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position + 0.5, 1.0);
        color = v_Color;
			}
		)";

    m_TriangleShader.reset(Engine::Shader::Create(vertexSrc, fragmentSrc));

    // Square Grid
    std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

    std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

      uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

    m_FlatColorShader.reset(Engine::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

    // Texture Shader
    std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

    std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

      uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

    m_TextureShader.reset(Engine::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));
    //m_Texture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");
    m_KirbyTexture = Engine::Texture2D::Create("assets/textures/Kirby.png");
    std::dynamic_pointer_cast<Engine::OpenGLShader>(m_TextureShader)->Bind();
    std::dynamic_pointer_cast<Engine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
  }

  // Inputs and Rendering are handled here
  void OnUpdate(Engine::Timestep dt) override 
  { 
    if (Engine::Input::IsKeyPressed((int)FunctionKeys::EN_KEY_LEFT))
    {
      m_CameraPosition.x -= m_CameraMoveSpeed * dt;
    }
    else if (Engine::Input::IsKeyPressed((int)FunctionKeys::EN_KEY_RIGHT))
    {
      m_CameraPosition.x += m_CameraMoveSpeed * dt;
    }

    if (Engine::Input::IsKeyPressed((int)FunctionKeys::EN_KEY_UP))
    {
      m_CameraPosition.y += m_CameraMoveSpeed * dt;
    }
    else if (Engine::Input::IsKeyPressed((int)FunctionKeys::EN_KEY_DOWN))
    {
      m_CameraPosition.y -= m_CameraMoveSpeed * dt;
    }

    if (Engine::Input::IsKeyPressed((int)PrintableKeys::EN_KEY_A))
    {
      m_CameraRotation += m_CameraRotationSpeed * dt;
    }                             
    if (Engine::Input::IsKeyPressed((int)PrintableKeys::EN_KEY_D))
    {                             
      m_CameraRotation -= m_CameraRotationSpeed * dt;
    }

    // LIGHTS! (clear screen)
    Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Engine::RenderCommand::Clear();

    // CAMERA! (set camera)
    m_Camera.SetPosition(m_CameraPosition);
    m_Camera.SetRotation(m_CameraRotation);

    // ACTION! (begin scene)
    Engine::Renderer::BeginScene(m_Camera);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

    for (int y = 0; y < 20; ++y)
    {
      for (int x = 0; x < 20; ++x)
      {
        glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
        Engine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
      }
    }
    //Engine::Renderer::Submit(m_Shader, m_VertexArray);
    //m_Texture->Bind();
    //Engine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    m_KirbyTexture->Bind();
    Engine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    // CUT! (end scene)
    Engine::Renderer::EndScene();
  }

  // Handles trigger events
  void OnEvent(Engine::Event& event) override 
  { 
  
  }

  // Renders ImGui windows
  virtual void OnImGuiRender() override
  {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
  }

private:
  Engine::Ref<Engine::Shader> m_TriangleShader;
  Engine::Ref<Engine::VertexArray> m_TriangleVA;
  Engine::Ref<Engine::Shader> m_FlatColorShader;
  Engine::Ref<Engine::Shader> m_TextureShader;
  Engine::Ref<Engine::VertexArray> m_SquareVA;
  Engine::Ref<Engine::Texture2D> m_Texture;
  Engine::Ref<Engine::Texture2D> m_KirbyTexture;
  Engine::OrthographicCamera m_Camera;
  glm::vec3 m_CameraPosition;
  float m_CameraMoveSpeed = 5.0f;
  float m_CameraRotation = 0.0f;
  float m_CameraRotationSpeed = 180.0f;
  glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

// Pushes current layer onto the stack
class Sandbox : public Engine::Application
{
public:
  Sandbox() 
  { 
    PushLayer(new ExampleLayer());
    //PushOverlay(new Engine::ImGuiLayer());
  }

  ~Sandbox() {}
};

// Creates the app
Engine::Application* Engine::CreateApplication()
{
  return new Sandbox();
}