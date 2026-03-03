#pragma once

#include <string>

struct GLFWwindow;

namespace UniverseEngine {

	class Window
	{
	public:
		Window(uint32_t width, uint32_t height, const std::string& title);
		~Window();

		void Update();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			uint32_t Width;
			uint32_t Height;
		};
		WindowData m_Data;
	};

}
