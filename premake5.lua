require "premake5/actions"

-------------------------------------------------------------------------------
-- Constants
-------------------------------------------------------------------------------
PROJECT_NAME = "InfixParser"

-------------------------------------------------------------------------------
-- The files and folders to delete when the "clean" action is run.
-------------------------------------------------------------------------------
action_clean_directories = {
	"./.vs",
	"./bin",
	"./obj",
	"./docs",
}	

action_clean_files = {
	"./".. PROJECT_NAME ..".vcxproj",
	"./".. PROJECT_NAME ..".vcxproj.filters",
	"./".. PROJECT_NAME ..".vcxproj.user",
	"./".. PROJECT_NAME .."Workspace.sln",
	"./".. PROJECT_NAME .."Workspace.VC.db",
	"./".. PROJECT_NAME .."Workspace.VC.VC.opendb"
}

-------------------------------------------------------------------------------
-- The main premake settings
-------------------------------------------------------------------------------
workspace(PROJECT_NAME .."Workspace")
	configurations {"Debug", "Release"}
	platforms {"Windows_x64"}
	characterset "Unicode"
	kind "ConsoleApp"
	language "C++"
	rtti "Off"
	warnings "Default"
	flags {"FatalWarnings"}
	targetdir "./bin/%{cfg.buildcfg}_%{cfg.platform}"
	objdir "./obj/%{prj.name}/%{cfg.buildcfg}_%{cfg.platform}"
	startproject(PROJECT_NAME .."Test")
	includedirs {
		"./include",
	}
	
	if (_ACTION == "vs2015" or _ACTION == "vs2017") then
		buildoptions{
			"/std:c++latest", -- Use the latest version of C++
			"/wd4996", -- Disable some warnings about things Visual Studio has taken apon itself to deem "deprecated"
		}
	end
	
	filter "platforms:Windows_x64"
        architecture "x64"
		defines {string.upper(PROJECT_NAME) .."_OS_WINDOWS"}
		
	filter "configurations:Debug"
		symbols "On"
		defines {"DEBUG"}
		
	filter "configurations:Release"
		optimize "Full"
		defines {"NDEBUG", "RELEASE"}

project(PROJECT_NAME)
	files {
		"./include/**",
		"./src/**",
	}
	debugdir "./src"
