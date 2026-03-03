#pragma once

#include "UniverseEngine/Core/Events/ApplicationEvents.h"

namespace UniverseEngine {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		void Initialise();
		void Shutdown();

		bool OnWindowClose(WindowCloseEvent& e);
	private:
		bool m_Running = false;
	};

	Application* CreateApplication(int argc, char** argv);

}
