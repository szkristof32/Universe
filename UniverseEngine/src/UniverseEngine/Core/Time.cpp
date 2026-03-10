#include "pch.h"
#include "Time.h"

#include <GLFW/glfw3.h>

namespace UniverseEngine {

	float Time::GetTime()
	{
		return static_cast<float>(glfwGetTime());
	}

}
