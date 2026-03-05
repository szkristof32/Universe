vendor = "%{wks.location}/UniverseEngine/vendor"

function ProcessDependencies()
	includedirs
	{
		"%{vendor}/glfw/include",
		"%{vendor}/glad/include",
		"%{vendor}/glm",
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
