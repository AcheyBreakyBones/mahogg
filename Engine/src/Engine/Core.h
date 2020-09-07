#pragma once

#include <memory>

#ifdef EN_PLATFORM_WINDOWS
// only build the DLL for import/export if Dynamic Linking is enabled
// otherwise, define ENGINE_API as empty to link statically
#if EN_DYNAMIC_LINK
  #ifdef EN_BUILD_DLL
    #define ENGINE_API __declspec(dllexport)
  #else
    #define ENGINE_API __declspec(dllimport)
  #endif
#else
  #define ENGINE_API
#endif
#else
  #error Engine only supports Windows!
#endif

#ifdef EN_DEBUG
  #define EN_ENABLE_ASSERTS
#endif

#ifdef EN_ENABLE_ASSERTS
  #define EN_ASSERT(x, ...) { if(!(x)) { EN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
  #define EN_CORE_ASSERT(x, ...) { if(!(x)) { EN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
  #define EN_ASSERT(x, ...)
  #define EN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

//#define EN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Engine
{
  template<typename T>
  using Scope = std::unique_ptr<T>;

  template<typename T>
  using Ref = std::shared_ptr<T>;
}