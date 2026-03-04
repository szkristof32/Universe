#include "pch.h"
#include "Window.h"

#include "UniverseEngine/Core/Application.h"

#include "UniverseEngine/Core/Events/ApplicationEvents.h"
#include "UniverseEngine/Core/Events/KeyboardEvents.h"
#include "UniverseEngine/Core/Events/MouseEvents.h"

#include <GLFW/glfw3.h>

namespace UniverseEngine {

	static void DebugCallback(int errorCode, const char* description)
	{
		std::cerr << "GLFW error: " << description << "\n";
	}

	Window::Window(uint32_t width, uint32_t height, const std::string& title)
		: m_Data{ width, height }
	{
		assert(glfwInit() && "Failed to initialise GLFW!");

		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef UE_DEBUG
		glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		glfwSetErrorCallback(DebugCallback);
#endif
		GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		assert(window && "Failed to create window!");

		const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowPos(window, (vidmode->width - width) / 2, (vidmode->height - height) / 2);

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		m_Window = window;
		glfwShowWindow(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowCloseEvent e;
			Application::Get()->OnEvent(e);
		});
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int32_t width, int32_t height)
		{
			WindowData& windowData = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			windowData.Width = width;
			windowData.Height = height;

			WindowResizeEvent e(width, height);
			Application::Get()->OnEvent(e);
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressEvent e(key);
					Application::Get()->OnEvent(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent e(key);
					Application::Get()->OnEvent(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressEvent e(key, true);
					Application::Get()->OnEvent(e);
					break;
				}
			}
		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t scancode)
		{
			KeyPressEvent e(scancode);
			Application::Get()->OnEvent(e);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			MouseMoveEvent e(static_cast<float>(xpos), static_cast<float>(ypos));
			Application::Get()->OnEvent(e);
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int32_t button, int32_t action, int32_t mods)
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressEvent e(button);
					Application::Get()->OnEvent(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleaseEvent e(button);
					Application::Get()->OnEvent(e);
					break;
				}
			}
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			MouseScrollEvent e(static_cast<float>(xoffset), static_cast<float>(yoffset));
			Application::Get()->OnEvent(e);
		});
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwPollEvents();
	}

}
