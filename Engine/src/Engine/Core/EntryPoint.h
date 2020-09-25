#pragma once
#include "Engine/Core/Core.h"

#ifdef EN_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
  //printf("MaHOG Engine\n");
  Engine::Log::Init();

  EN_PROFILE_BEGIN_SESSION("Initialization", "EngineProfile-Init.json");
  auto app = Engine::CreateApplication();
  EN_PROFILE_END_SESSION();

  EN_PROFILE_BEGIN_SESSION("Update", "EngineProfile-Update.json");
  app->Run();
  EN_PROFILE_END_SESSION();

  EN_PROFILE_BEGIN_SESSION("Exit", "EngineProfile-Exit.json");
  delete app;
  EN_PROFILE_END_SESSION();
}
#endif