#pragma once

#include "UniverseEngine/Core/Window.h"
#include "UniverseEngine/Core/LayerStack.h"

#include "UniverseEngine/Renderer/Renderer.h"

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

		static Reference<Application> Get();

		Reference<Window> GetWindow() const { return m_Window; }
	private:
		void Initialise();
		void Shutdown();

		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		
		LayerStack m_LayerStack;

		bool m_Running = false;
	};

	Application* CreateApplication(int argc, char** argv);

}
