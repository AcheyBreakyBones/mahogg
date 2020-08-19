workspace "Engine"
  architecture "x64"
  startproject "Sandbox"
  
  configurations
  {
    "Debug",
    "Release",
    "Dist"
  }
  
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "Engine/vendor/imgui"

include "Engine/vendor/GLFW"
include "Engine/vendor/Glad"
include "Engine/vendor/imgui"
  
project "Engine"
  location "Engine"
  kind "SharedLib"
  language "C++"
  staticruntime "off"
  
  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  pchheader "enpch.h"
  pchsource "Engine/src/enpch.cpp"
  
  files
  {
    "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
  }
  
  includedirs
  {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include",
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.Glad}",
    "%{IncludeDir.ImGui}"
  }

  links
  {
    "GLFW",
    "Glad",
    "ImGui",
    "opengl32.lib"
  }
  
  filter "system:windows"
    cppdialect "C++17"
    systemversion "latest"
    
    defines
    {
        "EN_PLATFORM_WINDOWS",
        "EN_BUILD_DLL",
        "GLFW_INCLUDE_NONE"
    }
    
    postbuildcommands
    {
      ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
    }
    
    filter "configurations:Debug"
      defines "EN_DEBUG"
      runtime "Debug"
      symbols "On"
    
    filter "configurations:Release"
      defines "EN_RELEASE"
      runtime "Release"
      optimize "On"
      
    filter "configurations:Dist"
      defines "EN_DIST"
      runtime "Release"
      optimize "On"
      
project "Sandbox"
  location "Sandbox"
  kind "ConsoleApp"
  language "C++"
  staticruntime "off"
  
  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
  
  files
  {
    "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
  }
  
  includedirs
  {
    "Engine/vendor/spdlog/include",
    "Engine/src"
  }
  
  links
  {
    "Engine"
  }
  
  filter "system:windows"
    cppdialect "C++17"
    systemversion "latest"
    
  defines
    {
        "EN_PLATFORM_WINDOWS"
    }
    
    filter "configurations:Debug"
      defines "EN_DEBUG"
      runtime "Debug"
      symbols "On"
    
    filter "configurations:Release"
      defines "EN_RELEASE"
      runtime "Release"
      optimize "On"
      
    filter "configurations:Dist"
      defines "EN_DIST"
      runtime "Release"
      optimize "On"