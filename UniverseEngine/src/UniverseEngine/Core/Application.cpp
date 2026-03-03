#include "pch.h"
#include "Application.h"

namespace UniverseEngine {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Initialise();

		while (m_Running)
		{
			WindowCloseEvent e;
			OnEvent(e);
		}

		Shutdown();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(UE_BIND_EVENT_FN(Application::OnWindowClose));
	}

	void Application::Initialise()
	{
		m_Running = true;
	}

	void Application::Shutdown()
	{
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
