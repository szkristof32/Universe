vendor = "%{wks.location}/UniverseEngine/vendor"

function ProcessDependencies()
	includedirs
	{
		"%{vendor}/glfw/include",
		"%{vendor}/glad/include",
		"%{vendor}/glm",
		"%{vendor}/memtrace_gtest",
		"%{vendor}/imgui",
	}

	links
	{
		"glfw3",
		"memtrace_gtest",
		"imgui",
	}

	libdirs
	{
		"%{vendor}/glfw/lib"
	}
end

project "memtrace_gtest"
	location "UniverseEngine/vendor/memtrace_gtest"
	kind "StaticLib"

	targetdir ("%{prj.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{prj.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
	}

project "imgui"
	location "UniverseEngine/vendor/imgui"
	kind "StaticLib"

	targetdir ("%{prj.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{prj.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
	}

	includedirs
	{
		"%{prj.location}",
		"%{vendor}/glfw/include"
	}
