workspace "Universe"
	configurations { "Debug", "Release" }
	startproject "Simulation"
	conformancemode "on"

	language "C++"
	cppdialect "C++11"
	staticruntime "off"
	architecture "x86_64"
	multiprocessorcompile "on"

	defines
	{
		"NOMINMAX"
	}

	filter "action:vs*"
        linkoptions { "/ignore:4099", "/ignore:4006" }
        disablewarnings { "4068", "4455" }
		buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

	filter "configurations:Debug"
		optimize "off"
		symbols "on"
		defines "UE_DEBUG"

	filter "configurations:Release"
		optimize "full"
		symbols "off"
		defines "UE_RELEASE"

	filter "system:windows"
		systemversion "latest"
		defines "UE_PLATFORM_WINDOWS"

	filter "system:linux"
		defines "UE_PLATFORM_LINUX"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "UniverseEngine"
include "Simulation"
