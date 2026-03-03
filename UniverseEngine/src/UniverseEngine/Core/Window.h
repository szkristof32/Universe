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

		GLFWwindow* GetWindowHandle() const { return m_Window; }
		uint32_t GetWidth() const { return m_Data.Width; }
		uint32_t GetHeight() const { return m_Data.Height; }
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
