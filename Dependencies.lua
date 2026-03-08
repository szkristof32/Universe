vendor = "%{wks.location}/UniverseEngine/vendor"

function ProcessDependencies()
	includedirs
	{
		"%{vendor}/glfw/include",
		"%{vendor}/glad/include",
		"%{vendor}/glm",
		"%{vendor}/memtrace_gtest",
	}

	links
	{
		"glfw3",
		"memtrace_gtest"
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
