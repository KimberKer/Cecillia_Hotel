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

include "Duck/vendor/GLFW"
include "Duck/vendor/Glad"
include "Duck/vendor/imgui"

-- Duck.dll
project "Duck"
	location "Duck"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

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
		"Duck/vendor",
		"Duck/vendor/spdlog/include",
        --"lib/glfw-3.3.8.bin.WIN64/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
    }

	-- Libs to Include, ".lib" files
	libdirs {
        --"lib/glfw-3.3.8.bin.WIN64/lib-vc2022"
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
		cppdialect "C++20"
		systemversion "latest"

		defines {
			"DUCK_PLATFORM_WINDOWS",
			"DUCK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			-- Copy Duck.dll into Sandbox
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "DUCK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "DUCK_RELEASE"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

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
		"Duck/vendor/spdlog/include",
		"%{IncludeDir.glm}"
		--"{prj.name}/src",
		--"lib/glfw-3.3.8.bin.WIN64/include"
	}

	-- Libs to Include, ".lib" files
	libdirs {
        --"lib/glfw-3.3.8.bin.WIN64/lib-vc2022"
    }

	links {
		"Duck"
		--"glfw3"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines {
			"DUCK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DUCK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "DUCK_RELEASE"
		runtime "Release"
		optimize "On"
