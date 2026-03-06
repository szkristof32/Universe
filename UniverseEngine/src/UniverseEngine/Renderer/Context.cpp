#include "pch.h"
#include "Context.h"

#include "UniverseEngine/Core/Application.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace UniverseEngine {

	static void DebugCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int length, const char* message, const void* userParam)
	{
		if (severity != GL_DEBUG_SEVERITY_HIGH) return;
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_NOTIFICATION:	std::cout << "OpenGL notification: " << message << "\n"; return;
			case GL_DEBUG_SEVERITY_LOW:				std::cout << "OpenGL info: " << message << "\n"; return;
			case GL_DEBUG_SEVERITY_MEDIUM:			std::cout << "OpenGL warning: " << message << "\n"; return;
			case GL_DEBUG_SEVERITY_HIGH:			std::cout << "OpenGL error: " << message << "\n"; return;
		}

		assert(false && "Unknown severity level!");
	}


	Context::Context()
		: m_Window(Application::Get()->GetWindow())
	{
		int version = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
		assert(version != 0 && "Failed to load OpenGL!");

#ifdef UE_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(DebugCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

		std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << "\n";
	}

	Context::~Context()
	{
	}

	void Context::BeginFrame() const
	{
		glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Context::EndFrame() const
	{
		glfwSwapBuffers(m_Window->GetWindowHandle());
	}

}
