#pragma once

#include <memory>

// While OpenGL is certainly a powerful API, it is not the most optimal choice
// for most platforms. For this reason, I decided to lay down the framework for
// multiple API support if I ever wish to implement them in the future.
// *Currently, only Windows x64 operating systems are supported*

// Automated platform detection using predefined macros
#ifdef _WIN32
	// Windows x64/x86
  #ifdef _WIN64
	  // Windows x64
    #define EN_PLATFORM_WINDOWS
  #else
	  // Windows x86
    #error "x86 Builds are not supported!"
  #endif
#elif defined(__APPLE__) || defined(__MACH__)
  #include <TargetConditionals.h>
  // TARGET_OS_MAC exists on all Apple platforms,
  // so all platforms must be checked (in this order)
  // to ensure that we're specifically running on MAC
  #if TARGET_IPHONE_SIMULATOR == 1
    #error "IOS simulator is not supported!"
  #elif TARGET_OS_IPHONE == 1
    #define EN_PLATFORM_IOS
    #error "IOS is not supported!"
  #elif TARGET_OS_MAC == 1
    #define EN_PLATFORM_MACOS
    #error "MacOS is not supported!"
  #else
    #error "Unknown Apple platform!"
  #endif
  //__ANDROID__ must be checked before __linux__
  // because Android is based off of the Linux kernel
  // i.e. __linux__ is defined in __ANDROID__
#elif defined(__ANDROID__)
  #define EN_PLATFORM_ANDROID
  #error "Android is not supported!"
#elif defined(__linux__)
  #define EN_PLATFORM_LINUX
  #error "Linux is not supported!"
#else
  // Unknown compiler/platform
  #error "Unknown platform!"
#endif // End of platform detection


// Currently, the Engine exports a static library (LIB) that gets imported into
// the target project to be statically linked. In my opinion, static linking is
// the superior option in this case because there is currently no need to swap
// libraries and a faster executable will be produced. However, if we ever 
// decide to switch to dynamic linking, DLL handling will be supported here
#ifdef EN_PLATFORM_WINDOWS
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
  #error Mercury only supports Windows!
#endif // End of DLL support

// EN_ASSERT and EN_CORE_ASSERT are used in the Debug configuration to help log
// specific build-breaking bugs in the target project and Engine, respectively
#ifdef EN_DEBUG
  #define EN_ENABLE_ASSERTS
#endif

#ifdef EN_ENABLE_ASSERTS
  #define EN_ASSERT(x, ...) { if(!(x)) { EN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
  #define EN_CORE_ASSERT(x, ...) { if(!(x)) { EN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
  #define EN_ASSERT(x, ...)
  #define EN_CORE_ASSERT(x, ...)
#endif // End of assert macros

//////////////////
// EVENT MACROS //
//////////////////
// Simple bit shift macro used for setting EventCategories in Event.h
#define BIT(x) (1 << x)

// Macro for binding event functions for use by EventDispatcher::Dispatch
#define EN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// In order to prevent memory leaks, all raw pointers will be replaced with
// smart pointers (unique and shared, depending on reference counting)
namespace Engine
{
  template<typename T>
  using Scope = std::unique_ptr<T>;
  template<typename T, typename ... Args>
  constexpr Scope<T> CreateScope(Args&& ... args)
  {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }

  template<typename T>
  using Ref = std::shared_ptr<T>;
  template<typename T, typename ... Args>
  constexpr Ref<T> CreateRef(Args&& ... args)
  {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
}
