project "ImGui"
    kind "StaticLib"
    staticruntime "on"
    
    language "C++"
    cppdialect "C++17"
-- Function to check if a command runs successfully
function commandExists(cmd)
    local handle = io.popen(cmd)
    local result = handle:read("*a")
    handle:close()
    return result ~= ""
end

-- Automatically initialize and update submodules if they aren't already.
if not os.isdir("Duck/vendor/GLFW/README.md") or 
   not os.isfile("Duck/vendor/spdlog/README.md") or
   not os.isfile("Duck/vendor/rapidjson/readme.md") or
   not os.isfile("Duck/vendor/imgui/premake5.lua") or
   not os.isfile("Duck/vendor/glm/readme.md") then
    -- Re-initialize and update submodules
    -- Try using WSL's git first
	if commandExists("wsl git --version") then
	os.execute("wsl git submodule update --init --recursive")
	-- Fallback to Windows' git
	elseif commandExists("git --version") then
	os.execute("git submodule update --init --recursive")
	else
	-- Handle error: neither WSL's git nor Windows' git is available
	print("Error: Git is not available in either WSL or Windows.")
	end
end

-- Solution File
workspace "Duck"
	startproject "Sandbox"
	architecture "x64"

    systemversion "latest"

  
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "imconfig.h",
        "imgui.h",
        "imgui.cpp",
        "imgui_draw.cpp",
        "imgui_internal.h",
        "imgui_widgets.cpp",
        "imgui_tables.cpp",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
        "imgui_demo.cpp",
        "imgui_impl_glfw.h",
        "imgui_impl_opengl3.h",
        "imgui_impl_opengl3_loader.h",
        "imgui_impl_glfw.cpp",
        "imgui_impl_opengl3.cpp"
    }

    
    --directories to include
    includedirs
    {
        "$(SolutionDir)extern/glfw-3.3.8.bin.WIN64/include",
        "%{IncludeDir.GLFW}"
    }

    links {
		    "GLFW"
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

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
