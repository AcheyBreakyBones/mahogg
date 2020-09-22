#pragma once
#include "Engine/Core/Core.h"

#ifdef EN_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
  //printf("MaHOG Engine\n");
  Engine::Log::Init();
  EN_CORE_WARN("Initialized Log!");
  int a = 5;
  EN_INFO("Hello! Var={0}", a);
  auto app = Engine::CreateApplication();
  app->Run();
  delete app;
}
#endif