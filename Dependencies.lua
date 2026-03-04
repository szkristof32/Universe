vendor = "%{wks.location}/UniverseEngine/vendor"

function ProcessDependencies()
	includedirs
	{
		"%{vendor}/glfw/include",
		"%{vendor}/glad/include",
	}

	links
	{
		"glfw3"
	}

	libdirs
	{
		"%{vendor}/glfw/lib"
	}
end
