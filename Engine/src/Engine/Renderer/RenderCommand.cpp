#include "enpch.h"
#include "Engine/Renderer/RenderCommand.h"

namespace Engine
{
  Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}