project "Simulation"
	kind "ConsoleApp"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"%{wks.location}/UniverseEngine/src"
	}

	links
	{
		"UniverseEngine"
	}

	filter "configurations:Release"
		kind "WindowedApp"
