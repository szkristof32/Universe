#pragma once

#include "UniverseEngine/Core/Window.h"

#include "UniverseEngine/Core/Events/ApplicationEvents.h"

#include <memory>

namespace UniverseEngine {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		static Application& Get();
	private:
		void Initialise();
		void Shutdown();

		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;

		bool m_Running = false;
	};

	Application* CreateApplication(int argc, char** argv);

}
