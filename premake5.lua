project "Box2D"
  kind "StaticLib"
  language "C++"
  cppdialect "C++20"

  targetdir ("bin/"..outputdir.."/%{prj.name}")
  objdir ("bin-int/"..outputdir.."/%{prj.name}")

  files {
    "src/**.h",
    "src/**.cpp",
    "include/**.h"
  }

  includedirs{
      "include",
      "src"
  }

  filter "system:windows"
    systemversion "latest"
    staticruntime "on"

  filter "configurations:Debug"
    defines "BL_DEBUG"
    symbols "on"
    runtime "Debug"
  
  filter "configurations:Release"
    defines "BL_RELEASE"
    optimize "on"
    runtime "Release"

  filter "configurations:Dist"
	optimize "on"
	runtime "Release"