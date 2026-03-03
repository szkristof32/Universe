project "UniverseEngine"
	kind "StaticLib"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"vendor/glfw/include"
	}

	defines
	{
		"GLFW_INCLUDE_NONE"
	}

	links
	{
		"glfw3"
	}

	libdirs
	{
		"vendor/glfw/lib"
	}
