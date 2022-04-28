-- require "export-compile-commands"

newoption {
	trigger = "cppnative",
	description = "use winmain in cpp project instead of export to dll for csproj"
}

workspace "Doud"
	configurations {"Debug", "Release"}
	architecture "x86_64"
	language "c++"
	cppdialect "c++17"
	characterset ("Unicode")


include "./vendor/glad"
include "./vendor/imgui"

project "dcore"
	kind "SharedLib"
	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}"
	objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}"

	defines {
	    "DOVE_EXPORT_DLL"
	}

	includedirs {
		"src/",
		"vendor/",
		"vendor/glad/include",
	}

	files {
		"src/*.h", 
		"src/*/*.h", 
		"src/*/*/*.h", 
		"vendor/stb_image/*.h",

		"src/*.cpp", 
		"src/*/*.cpp", 
		"src/*/*/*.cpp", 
		"vendor/stb_image/*.cpp",
	}

	links {
		"opengl32",
		"ImGui",
		"glad",
	}

	staticruntime "On"

filter "configurations:Debug"
	symbols "On"
	defines {"DEBUG"}

filter "options:cppnative"
	kind "WindowedApp"
    defines {"DOVE_CPP_NATIVE"}