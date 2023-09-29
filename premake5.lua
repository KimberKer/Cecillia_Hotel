-- Solution File
workspace "Duck"
	startproject "Sandbox"
	architecture "x64"

	configurations {
		"Debug",
		"Release"
	}

-- Output Directory Shortcut
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Duck/vendor/GLFW/include"
IncludeDir["Glad"] = "Duck/vendor/Glad/include"
IncludeDir["glm"] = "Duck/vendor/glm"
IncludeDir["ImGui"] = "Duck/vendor/imgui"
IncludeDir["FMODcore"] = "Duck/vendor/FMOD/api/core/inc"
IncludeDir["FMODstudio"] = "Duck/vendor/FMOD/api/studio/inc"

include "Duck/vendor/GLFW"
include "Duck/vendor/Glad"
include "Duck/vendor/imgui"


-- Duck.dll
project "Duck"
	location "Duck"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	-- Output Directory
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")

	-- Intermediates Directory
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "duckpch.h"
	pchsource "Duck/src/duckpch.cpp"

	-- Files to Generate
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	-- Directories to Include
    includedirs {
		"%{prj.name}/src",
		"Duck/vendor/spdlog/include",
        --"lib/glfw-3.3.8.bin.WIN64/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.FMODcore}",
		"%{IncludeDir.FMODstudio}"
    }

	-- Libs to Include, ".lib" files
	libdirs {
        --"lib/glfw-3.3.8.bin.WIN64/lib-vc2022"
		"Duck/vendor/FMOD/api/core/lib",
		"Duck/vendor/FMOD/api/studio/lib"
    }

	-- Link Input .dll
	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
        --"glfw3"
    }

	filter "system:windows"

	systemversion "latest"

	defines {
		"DUCK_PLATFORM_WINDOWS",
		"DUCK_BUILD_DLL",
		"GLFW_INCLUDE_NONE",
		"_CRT_SECURE_NO_WARNINGS"
	}


	filter "configurations:Debug"
		defines "DUCK_DEBUG"
		runtime "Debug"
		symbols "On"
		links { "fmod_vc.lib", "fmodstudio_vc.lib" }
		postbuildcommands {
			("{COPY} %{wks.location}/Duck/vendor/FMOD/api/core/lib/fmod.dll \"../bin/" ..outputdir.. "/Sandbox/\""),
			("{COPY} %{wks.location}/Duck/vendor/FMOD/api/studio/lib/fmodstudio.dll \"../bin/" ..outputdir.. "/Sandbox/\"")
		}

	filter "configurations:Release"
		defines "DUCK_RELEASE"
		runtime "Release"
		optimize "On"
		links { "fmodL.lib", "fmodstudioL_vc.lib" }
		postbuildcommands {
			("{COPY} %{wks.location}/Duck/vendor/FMOD/api/core/lib/fmodL.dll \"../bin/" ..outputdir..  "/Sandbox/\""),
			("{COPY} %{wks.location}/Duck/vendor/FMOD/api/studio/lib/fmodstudioL.dll \"../bin/" ..outputdir..  "/Sandbox/\"")
		}


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	-- Output Directory
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")

	-- Intermediates Directory
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	-- Files to Generate
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	-- Directories to Include
	includedirs {
		"Duck/src",
		"Duck/vendor",
		"Duck/vendor/spdlog/include",
		"%{IncludeDir.glm}",
		"%{IncludeDir.FMODcore}",
		"%{IncludeDir.FMODstudio}"
		
		--"{prj.name}/src",
		--"lib/glfw-3.3.8.bin.WIN64/include"
	}

	-- Libs to Include, ".lib" files
	libdirs {
        --"lib/glfw-3.3.8.bin.WIN64/lib-vc2022"
		"Duck/vendor/FMOD/api/core/lib",
		"Duck/vendor/FMOD/api/studio/lib"
    }

	links {
		"Duck"
		--"glfw3"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"DUCK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DUCK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DUCK_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "DUCK_DIST"
		runtime "Release"
		optimize "on"

