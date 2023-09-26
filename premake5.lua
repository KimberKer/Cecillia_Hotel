-- Solution File
workspace "Duck"
	startproject "Sandbox"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
	}

-- Output Directory Shortcut
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Duck.dll
project "Duck"
	location "Duck"
	kind "SharedLib"
	language "C++"

	-- Output Directory
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")

	-- Intermediates Directory
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- Files to Generate
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	-- Directories to Include
    includedirs {
        "lib/glfw-3.3.8.bin.WIN64/include",
		"lib/FMOD Studio API Windows/api/core/inc",
		"lib/FMOD Studio API Windows/api/studio/inc"
    }

	-- Libs to Include, ".lib" files
	libdirs {
        "lib/glfw-3.3.8.bin.WIN64/lib-vc2022",
		"lib/FMOD Studio API Windows/api/core/lib/x64",
		"lib/FMOD Studio API Windows/api/studio/lib/x64"
    }

	-- Link Input .dll
	links {
        "glfw3",
		"fmod_vc",
		"fmodstudio_vc"
    }

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"

		defines {
			"DUCK_PLATFORM_WINDOWS",
			"DUCK_BUILD_DLL"
		}

		postbuildcommands {
			-- Copy Duck.dll into Sandbox
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")

		}

	filter "configurations:Debug"
		defines "DUCK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DUCK_RELEASE"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	-- Output Directory
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")

	-- Intermediates Directory
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	-- Files to Generate
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	-- Directories to Include
	includedirs {
		"Duck/src",
		"lib/glfw-3.3.8.bin.WIN64/include",
		"lib/FMOD Studio API Windows/api/core/inc",
		"lib/FMOD Studio API Windows/api/studio/inc"
	}

	-- Libs to Include, ".lib" files
	libdirs {
        "lib/glfw-3.3.8.bin.WIN64/lib-vc2022",
		"lib/FMOD Studio API Windows/api/core/lib/x64",
		"lib/FMOD Studio API Windows/api/studio/lib/x64"
    }

	links {
		"Duck",
		"glfw3",
		"fmod_vc",
		"fmodstudio_vc"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"

		defines {
			"DUCK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DUCK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DUCK_RELEASE"
		optimize "On"
